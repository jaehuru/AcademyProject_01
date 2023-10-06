// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniProject.h"
#include "GameFramework/Actor.h"
#include "MP_WP_Actor.generated.h"

UCLASS()
class MINIPROJECT_API AMP_WP_Actor : public AActor
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComponent;

public:	
	// Sets default values for this actor's properties
	AMP_WP_Actor();

	inline int GetAmmoCount() { return _ammoCount;  }
	inline float GetReloadingDelayTime() { return _reloadingDelayTime;  }

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	int _ammoCount = 30;
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float _reloadingDelayTime = 3.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

};
