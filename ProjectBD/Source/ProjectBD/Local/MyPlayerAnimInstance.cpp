// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerAnimInstance.h"
#include "Local/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//���� �ִϸ��̼��� ������ ���� ����ص� �Ǵ� Pawn Ŭ���� ���� Ȯ��
	//��� �ص� �Ǵ� �������� Ȯ��
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
	}
}
