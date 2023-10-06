// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_AnimInstance.h"

UMP_AnimInstance::UMP_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UMP_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}
