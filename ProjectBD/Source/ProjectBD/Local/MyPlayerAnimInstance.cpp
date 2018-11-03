// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerAnimInstance.h"
#include "Local/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StreamableManager.h"

void UMyPlayerAnimInstance::NativeInitializeAnimation()
{
	FStreamableManager Loader;
	FStringAssetReference MontagePath(
		TEXT("AnimMontage'/Game/Male_Grunt/Animations/Reload_Rifle_Hip_Montage.Reload_Rifle_Hip_Montage'"));
	ReloadMontage = Loader.LoadSynchronous<UAnimMontage>(MontagePath);
}

void UMyPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//현재 애니메이션의 주인이 내가 사용해도 되는 Pawn 클래스 인지 확인
	//사용 해도 되는 상태인지 확인
	AMyPlayer* Pawn = Cast<AMyPlayer>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity,
			Pawn->GetActorRotation());

		bIsCrouch = Pawn->bIsCrouched;

		AimYaw = Pawn->GetAimOffset().Yaw;
		AimPitch = Pawn->GetAimOffset().Pitch;

		bIsIronsight = Pawn->bIsIronsight;
		bIsSprint = Pawn->bIsSprint;

		CurrentLeanType = Pawn->CurrentLeanType;

		float TargetLeanAngle = 0;
		if (CurrentLeanType == EPlayerLeanType::Left)
		{
			TargetLeanAngle = -30.0f;
		}
		else if (CurrentLeanType == EPlayerLeanType::Right)
		{
			TargetLeanAngle = 30.0f;
		}
		else //Normal
		{
			TargetLeanAngle = 0;
		}

		bLeftLean = Pawn->bLeftLean;
		bRightLean = Pawn->bRightLean;

		if (bLeftLean)
		{
			TargetLeanAngle = -30.0f;
		}
		else if (bRightLean)
		{
			TargetLeanAngle = 30.0f;
		}
		else //Normal
		{
			TargetLeanAngle = 0;
		}

		CurrentLeanAngle = FMath::FInterpTo(CurrentLeanAngle,
			TargetLeanAngle,
			DeltaSeconds,
			15);

		bIsReload = Pawn->bIsReload;
		if (bIsReload)
		{
			Montage_Play(ReloadMontage);
			bIsReload = false;
			Pawn->bIsReload = false;
		}

		bIsFire = Pawn->bIsFire;
	}
}
