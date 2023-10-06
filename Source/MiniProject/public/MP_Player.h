// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MiniProject.h"
#include "GameFramework/Character.h"
#include "MP_Player.generated.h"

UCLASS()
class MINIPROJECT_API AMP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		THIRDPEOPLE,
		FIRSTPERSON,
		// �Ʒ��� �߰�. ������ �̵��������� ȸ���ϱ� ���� �ڵ� ����
		ENEMY
	};

	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::THIRDPEOPLE;
	FVector DirectionToMove = FVector::ZeroVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* ArmMesh;

	// �Ʒ��� �߰�. ������ �̵��������� ȸ���ϱ� ���� �ڵ� ����
	virtual void PossessedBy(AController* NewController) override;




private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ViewChange();
};
