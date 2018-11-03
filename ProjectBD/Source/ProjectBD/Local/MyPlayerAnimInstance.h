// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Local/MyPlayer.h"

#include "MyPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class UAnimMontage* ReloadMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bIsCrouch = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float AimPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bIsIronsight = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bIsSprint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	EPlayerLeanType CurrentLeanType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float CurrentLeanAngle;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Info")
	bool bLeftLean = false;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Info")
	bool bRightLean = false;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Info")
	bool bIsReload = false;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Info")
	bool bIsFire = false;
};
