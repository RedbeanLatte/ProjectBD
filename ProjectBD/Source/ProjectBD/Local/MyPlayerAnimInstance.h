// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UMyPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	bool bIsCrouch = false;
};
