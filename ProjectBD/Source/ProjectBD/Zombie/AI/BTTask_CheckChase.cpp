// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CheckChase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Zombie/ZombieAIController.h"
#include "Zombie/Zombie.h"
#include "Perception/PawnSensingComponent.h"

// 원래 태스크는 특정 클래스에 종속되면 안된다, 블랙보드만 참고하도록 설계 할것 
EBTNodeResult::Type UBTTask_CheckChase::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
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
				if (Zombie->PawnSensing->SightRadius < Distance)
				{
					Zombie->CurrentState = EZombieState::Normal;
					AIC->SetCurrentState(Zombie->CurrentState);
				}
				else if (Zombie->AttackRange >= Distance)
				{
					Zombie->CurrentState = EZombieState::Battle;
					AIC->SetCurrentState(Zombie->CurrentState);
				}
			}
		}
	}

	return EBTNodeResult::Succeeded;
}
