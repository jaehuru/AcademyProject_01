// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_AIController.h"
//#include "NavigationSystem.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMP_AIController::HomePosKey(TEXT("HomePos"));
const FName AMP_AIController::PatrolPoskey(TEXT("PatrolPos"));
const FName AMP_AIController::Targetkey(TEXT("Target"));

AMP_AIController::AMP_AIController()
{
	//RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/_ProjectSettings/AI/BB_MPCharacter.BB_MPCharacter'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/_ProjectSettings/AI/BT_MPCharacter.BT_MPCharacter'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AMP_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AMP_AIController::OnRepeatTimer, RepeatInterval, true);

	/* 이렇게 책대로 하면 안됨. 그래서 아래와 같이 바꿈.
	if (UseBlackboard(BBAsset, Blackboard))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
	*/
	UBlackboardComponent* TmpBB = Cast<UBlackboardComponent>(Blackboard);
	if (UseBlackboard(BBAsset, TmpBB))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}



}

//void AMP_AIController::OnUnPossess()
//{
//	Super::OnUnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//}



//void AMP_AIController::OnRepeatTimer()
//{
//
//	auto CurrentPawn = GetPawn();
//	if(nullptr != CurrentPawn)
//	{
//		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//		if (nullptr == NavSystem) return;
//		
//		FNavLocation NextLocation;
//		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
//		{
//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
////			ABLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString()); 책대로하면 안됨
//			UE_LOG(LogTemp, Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
//		}
//	}
//}

