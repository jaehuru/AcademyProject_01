
#include "MP_Enemy.h"
#include "MP_AIController.h"


AMP_Enemy::AMP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// NPC�� ���̷�Ż �Žð� �� ������Ʈ �����ϰ� ��Ʈ������Ʈ�� ����.
	pEnemyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ENEMY"));
	RootComponent = pEnemyMeshComp;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ENEMY_BODY(TEXT("/Script/Engine.SkeletalMesh'/Game/_ProjectSettings/Mesh/Enemy_01.Enemy_01'"));
	if (ENEMY_BODY.Succeeded())
	{
		pEnemyMeshComp->SetSkeletalMesh(ENEMY_BODY.Object);
	}

	// NPC���� AI ��Ʈ�ѷ� ����
	AIControllerClass = AMP_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//---------------�߰��κ�-----------
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(TEXT("/Script/Engine.AnimBlueprint'/Game/_ProjectSettings/Blueprints/MP_BP_Player_C'"));
	if (ENEMY_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);
	}


	//-------------�������-----------


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

