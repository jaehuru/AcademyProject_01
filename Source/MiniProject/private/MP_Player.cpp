// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Player.h"

// Sets default values
AMP_Player::AMP_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN(TEXT("/Script/Engine.SkeletalMesh'/Game/Man/Mesh/Full/SK_Man_Full_02.SK_Man_Full_02'"));
	if (SK_MAN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAN.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(TEXT("/Script/Engine.AnimBlueprint'/Game/_ProjectSettings/Blueprints/MP_BP_Player.MP_BP_Player_C'"));
	if (PLAYER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMesh"));
	ArmMesh->SetupAttachment(GetMesh(), TEXT("ArmMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/_ProjectSettings/Mesh/SK_Man_Arms.SK_Man_Arms'"));
	if (ArmMeshAsset.Succeeded())
	{
		ArmMesh->SetSkeletalMesh(ArmMeshAsset.Object);
	}

	ArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ARM_ANIM(TEXT("/Script/Engine.AnimBlueprint'/Game/_ProjectSettings/Blueprints/MP_BP_Player.MP_BP_Player_C'"));
	if (ARM_ANIM.Succeeded())
	{
		ArmMesh->SetAnimInstanceClass(ARM_ANIM.Class);
	}

	
	ArmMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	SetControlMode(EControlMode::THIRDPEOPLE);

	GetCharacterMovement()->JumpZVelocity = 450.0f;

}

// Called when the game starts or when spawned
void AMP_Player::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMP_Player::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::THIRDPEOPLE: 
		SpringArm->TargetArmLength = 250.f;
		SpringArm->TargetOffset = FVector(0.f, 0.f, 55.f);
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = true;
		if (ArmMesh)
		{
			ArmMesh->SetVisibility(false);
		}
		GetMesh()->SetVisibility(true);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::FIRSTPERSON:
		SpringArm->TargetArmLength = -25.f;
		SpringArm->TargetOffset = FVector(-9.7f, 2.5f, 40.f);
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = true;
		if (ArmMesh)
		{
			ArmMesh->SetVisibility(true);
		}
		GetMesh()->SetVisibility(false);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
		// 아래항 추가. 적군이 이동방향으로 회전하기 위한 코드 생성
	case EControlMode::ENEMY:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		break;
		// 여기까지

	}
}

// Called every frame
void AMP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AMP_Player::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMP_Player::Jump);


	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMP_Player::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMP_Player::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMP_Player::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMP_Player::Turn);

	
}



void AMP_Player::UpDown(float NewAxisValue)
{
	// 현재 플레이어의 시선 방향을 가져옴
	FRotator ControlRotation = GetControlRotation();

	// 시선 방향의 피치 회전을 0으로 만들어 위아래로 바라볼 때 이동 방향이 변하지 않도록 함
	ControlRotation.Pitch = 0.0f;

	// 시선 방향에 따라 이동 방향을 설정
	FVector MoveDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);

	// 이동 입력에 이동 방향을 적용
	AddMovementInput(MoveDirection, NewAxisValue);

}


void AMP_Player::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}


void AMP_Player::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}


void AMP_Player::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}


void AMP_Player::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::THIRDPEOPLE:
		SetControlMode(EControlMode::FIRSTPERSON);
		break;
	case EControlMode::FIRSTPERSON:
		SetControlMode(EControlMode::THIRDPEOPLE);
		break;
	
	}
}

// 아래항 추가. 적군이 이동방향으로 회전하기 위한 코드 생성-----------
void AMP_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (IsPlayerControlled())
	{
		/*
		* 재후님. 이부분을 활성화 하려면 이득우에서 컨트롤모드 부분을 완성해주셔야 해요. 이게 ENEMY AI와 연동됩니다.
		* 완성되고 나면 주석을 해제하시면 됩니다. 
		SetControlMode(EControlMode::DIABLO);
		*/

		GetCharacterMovement()-> MaxWalkSpeed = 600.0f;
	}
	else
	{
		SetControlMode(EControlMode::ENEMY);
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}
// 여기까지-------------------------------------------------------