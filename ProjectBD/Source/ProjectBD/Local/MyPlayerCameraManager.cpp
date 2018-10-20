// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCameraManager.h"
#include "Local/LocalPC.h"
#include "Local/MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"

void AMyPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	AMyPlayer* Pawn = Cast<AMyPlayer>(PCOwner->GetPawn());

	if (Pawn)
	{
		//FOV를 부드럽게 변환
		float TargetFOV = Pawn->bIsIronsight ? IronsightFOV : NormalFOV;
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 15.0f);
		SetFOV(DefaultFOV);

		//SpringArm 위치를 부드럽게 변환
		FVector TargetPosition = Pawn->bIsCrouched ? Pawn->CrouchSpringArmPosition : Pawn->NormalSpringArmPosition;
		DefaultPosition = FMath::VInterpTo(DefaultPosition, TargetPosition, DeltaTime, 15.0f);
		Pawn->SpringArm->SetRelativeLocation(DefaultPosition);
	}
}
