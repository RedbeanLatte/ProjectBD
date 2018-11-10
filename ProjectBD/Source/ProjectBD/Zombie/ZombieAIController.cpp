// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AZombieAIController::AZombieAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void AZombieAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GetPawn()
}

void AZombieAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie && Zombie->BehaviorTree && Zombie->BehaviorTree->BlackboardAsset)
	{
		BBComponent->InitializeBlackboard(*(Zombie->BehaviorTree->BlackboardAsset));
		BTComponent->StartTree(*(Zombie->BehaviorTree));

		//BBComponent->SetValueAsVector(FName(TEXT("Target")), FVector(900, 800, 120));
	}
}

void AZombieAIController::UnPossess()
{
	BTComponent->StopTree();
}

void AZombieAIController::SetTarget(AActor * Target)
{
	BBComponent->SetValueAsObject(FName(TEXT("Target")), Target);
}

void AZombieAIController::SetCurrentState(EZombieState NewState)
{
	BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)NewState);
}
