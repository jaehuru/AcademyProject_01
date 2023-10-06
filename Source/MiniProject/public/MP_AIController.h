// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniProject.h"
#include "AIController.h"
#include "MP_AIController.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT_API AMP_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AMP_AIController();
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPoskey;
	static const FName Targetkey;

private:
	//void OnRepeatTimer();

	//FTimerHandle RepeatTimerHandle;
	//float RepeatInterval;	

	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

};
