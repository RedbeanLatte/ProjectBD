// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void UpdateCamera(float DeltaTime) override;
	
	float NormalFOV = 90.0f;
	float IronsightFOV = 60.0f;

	FVector DefaultPosition; // ÇöÀç SpringArm Position

};
