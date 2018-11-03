// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie/Zombie.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieAIController();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBehaviorTreeComponent* BTComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBlackboardComponent* BBComponent;

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	void SetTarget(AActor* Target);

	void SetCurrentState(EZombieState NewState);
};
