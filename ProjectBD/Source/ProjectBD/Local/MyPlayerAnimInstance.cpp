// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerAnimInstance.h"
#include "Local/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	}
}
