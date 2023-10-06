
#pragma once

#include "MiniProject.h"
#include "GameFramework/Character.h"
#include "MP_Enemy.generated.h"

UCLASS()
class MINIPROJECT_API AMP_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	AMP_Enemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* pEnemyMeshComp;



};
