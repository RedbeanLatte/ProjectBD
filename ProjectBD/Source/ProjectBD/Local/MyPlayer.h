// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UENUM(BlueprintType)
enum class EPlayerLeanType : uint8
{
	Normal = 0	UMETA(Display = "Normal"),
	Left = 1	UMETA(Display = "Left"),
	Right = 2	UMETA(Display = "Right")
};

UCLASS()
class PROJECTBD_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Weapon;

	// Ironsight 동작용
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="State")
	bool bIsIronsight = false;

	// Sprint 동작용
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "State")
	bool bIsSprint = false;
	
	void Forward(float Value);
	void Right(float Value);
	void Pitch(float Value);
	void Yaw(float Value);

	void Crouching();
	void DoIronsight();
	void StartSprint();
	void StopSprint();

	FRotator GetAimOffset() const;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float SprintSpeed = 800.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float JogSpeed = 450.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float IronsightSpeed = 150.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	float CrouchSpeed = 150.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	FVector NormalSpringArmPosition;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	FVector CrouchSpringArmPosition;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "State")
	bool bIsFire = false;

	void StartFire();
	void StopFire();
	void OnShoot();

	FTimerHandle ShootTimer;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* FireEffect;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* HitEffect;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effect")
	class UParticleSystem* BloodEffect;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effect")
	class USoundBase* FireSound;
	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effect")
	class UMaterialInterface* BulletDecal;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Health")
	float CurrentHP = 100.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Health")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* DeadAnimation;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* ReloadAnimation;

	void DeadProcess();
	
	void StartLeanLeft();
	void StopLeanLeft();
	void StartLeanRight();
	void StopLeanRight();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	EPlayerLeanType CurrentLeanType = EPlayerLeanType::Normal;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	bool bLeftLean = false;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	bool bRightLean = false;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Animation")
	bool bIsReload = false;

	void Reload();

	TArray<class AMasterItem*> GetItemList;

	void AddItemList(class AMasterItem* Item);
	void RemoveItemList(class AMasterItem* Item);

	int GetClosestItem();

	void PickupItem();

	void ShowInventory();
};
