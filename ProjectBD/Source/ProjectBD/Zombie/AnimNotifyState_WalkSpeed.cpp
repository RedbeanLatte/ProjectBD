// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_WalkSpeed.h"
#include "Components/SkeletalMeshComponent.h"
#include "Zombie/Zombie.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotifyState_WalkSpeed::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AZombie* Pawn = Cast<AZombie>(MeshComp->GetOwner());
	if (Pawn && Pawn->CurrentState == EZombieState::Normal)
	{
		Pawn->GetCharacterMovement()->MaxWalkSpeed = 10.0f;
	}
}

void UAnimNotifyState_WalkSpeed::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_WalkSpeed::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AZombie* Pawn = Cast<AZombie>(MeshComp->GetOwner());
	if (Pawn && Pawn->CurrentState == EZombieState::Normal)
	{
		Pawn->GetCharacterMovement()->MaxWalkSpeed = Pawn->WalkSpeed;
	}
}
