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
	}
}
