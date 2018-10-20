// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class PROJECTBD_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Weapon;

	// Ironsight 동작용
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="State")
	bool bIsIronsight = false;

	// Sprint 동작용
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
	bool bIsSprint = false;
	
	void Forward(float Value);
	void Right(float Value);
	void Pitch(float Value);
	void Yaw(float Value);

	void Crouching();
	void DoIronsight();
	void StartSprint();
	void StopSprint();

	FRotator GetAimOffset() const;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float SprintSpeed = 800.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float JogSpeed = 450.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float IronsightSpeed = 150.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float CrouchSpeed = 150.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	FVector NormalSpringArmPosition;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	FVector CrouchSpringArmPosition;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	bool bIsFire = false;

	void StartFire();
	void StopFire();
	void OnShoot();

	FTimerHandle ShootTimer;
};
