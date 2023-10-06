
#include "MP_Enemy.h"
#include "MP_AIController.h"


AMP_Enemy::AMP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// NPC의 스켈레탈 매시가 들어갈 컴포넌트 선언하고 루트컴포넌트를 지정.
	pEnemyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ENEMY"));
	RootComponent = pEnemyMeshComp;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ENEMY_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/_ProjectSettings/Mesh/Enemy_01.Enemy_01'"));
	if (ENEMY_BODY.Succeeded())
	{
		pEnemyMeshComp->SetSkeletalMesh(ENEMY_BODY.Object);
	}

	// NPC에게 AI 컨트롤러 맵핑
	AIControllerClass = AMP_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//---------------추가부분-----------
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(TEXT("/Script/Engine.AnimBlueprint'/Game/_ProjectSettings/Blueprints/MP_BP_Player_C'"));
	if (ENEMY_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);
	}


	//-------------여기까지-----------


}


void AMP_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMP_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

