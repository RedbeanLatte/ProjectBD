// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetRandomPatrolPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Zombie/PatrolPoint.h"
#include "Engine/World.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		APatrolPoint::StaticClass(),
		Result);

	if (Result.Num() > 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(),
			Result[FMath::RandRange(0, Result.Num() - 1)]);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}
