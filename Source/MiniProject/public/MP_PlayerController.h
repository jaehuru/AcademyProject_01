// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniProject.h"
#include "GameFramework/PlayerController.h"
#include "MP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT_API AMP_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
