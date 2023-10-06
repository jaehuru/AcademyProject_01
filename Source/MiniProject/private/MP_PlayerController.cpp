// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_PlayerController.h"

void AMP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
