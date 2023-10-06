// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_WP_Actor.h"

// Sets default values
AMP_WP_Actor::AMP_WP_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MP_WEAPON(TEXT("/Script/Engine.SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A'"));
	if (MP_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(MP_WEAPON.Object);
	}

	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AMP_WP_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMP_WP_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

