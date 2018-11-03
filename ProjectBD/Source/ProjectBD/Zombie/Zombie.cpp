// Fill out your copyright notice in the Description page of Project Settings.

#include "Zombie.h"
#include "Perception/PawnSensingComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Zombie/ZombieAIController.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->HearingThreshold = 2000.0f;
	PawnSensing->LOSHearingThreshold = 5000.0f;
	PawnSensing->SetPeripheralVisionAngle(60.0f);
	PawnSensing->SightRadius = 400.0f;
	PawnSensing->SensingInterval = 0.1f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	static ConstructorHelpers::FClassFinder<AAIController> BP_AI(TEXT("Blueprint'/Game/Blueprints/Zombie/BP_ZombieAIController.BP_ZombieAIController_C'"));
	if (BP_AI.Succeeded())
	{
		//AIControllerClass = AZombieAIController::StaticClass();
		AIControllerClass = BP_AI.Class;
	}
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AZombie::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

