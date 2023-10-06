// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniProject.h"
#include "Animation/AnimInstance.h"
#include "MP_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT_API UMP_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMP_AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
};
