// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Box.h"
#include "MP_WP_Actor.h"

// Sets default values
AMP_Box::AMP_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	
	Trigger->SetBoxExtent(FVector::ZeroVector);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MP_BOX(TEXT("/Script/Engine.StaticMesh'/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'"));
	if (MP_BOX.Succeeded())
	{
		Box->SetStaticMesh(MP_BOX.Object);
	}

	Box->SetRelativeLocation(FVector::ZeroVector);

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = AMP_WP_Actor::StaticClass();
}

// Called when the game starts or when spawned
void AMP_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMP_Box::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMP_Box::OnCharactertOverlap);
}

// Called every frame
void AMP_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMP_Box::OnCharactertOverlap(UPrimitiveComponent* OverlapperComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ABLOG_S(Warning);
}

