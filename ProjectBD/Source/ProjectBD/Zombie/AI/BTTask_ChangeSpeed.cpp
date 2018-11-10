// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ChangeSpeed.h"
#include "Zombie/Zombie.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Zombie/ZombieAIController.h"

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if (Zombie)
	{
		Zombie->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}

	return EBTNodeResult::Succeeded;
}
