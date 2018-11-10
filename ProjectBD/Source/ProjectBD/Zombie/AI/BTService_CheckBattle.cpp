// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckBattle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Zombie/ZombieAIController.h"
#include "Zombie/Zombie.h"

void UBTService_CheckBattle::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AZombieAIController* AIC = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		AZombie* Zombie = Cast<AZombie>(AIC->GetPawn());
		if (Zombie)
		{
			AActor* Player = Cast<AActor>(AIC->BBComponent->GetValueAsObject(FName(TEXT("Target"))));
			if (Player)
			{
				float Distance = FVector::Distance(Zombie->GetActorLocation(), Player->GetActorLocation());
				if (Zombie->AttackRange < Distance)
				{
					Zombie->CurrentState = EZombieState::Chase;
					AIC->SetCurrentState(Zombie->CurrentState);
				}
			}
		}
	}
}
