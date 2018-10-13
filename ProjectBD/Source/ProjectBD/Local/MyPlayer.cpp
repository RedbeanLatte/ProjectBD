// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "ProjectBD.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("RHandWeapon"));

	// 권고 사항은 하드코딩 하지 말기, 로딩 할때 메시로딩 해서 느림, 생성자용
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh(TEXT("SkeletalMesh'/Game/Male_Grunt/Mesh/male_grunt.male_grunt'"));
	if (SK_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Wepon(TEXT("StaticMesh'/Game/Weapons/M4A1/SM_M4A1.SM_M4A1'"));
	if (SM_Wepon.Succeeded())
	{
		Weapon->SetStaticMesh(SM_Wepon.Object);
	}

	//메시의 방향과 위치 조정
	GetMesh()->SetRelativeLocation(FVector(0, 
		0,
		-GetCapsuleComponent()->GetScaledCapsuleHalfHeight())
	);

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//메시에 애니메이션 블루프린트 연결, _C 추가, 생성자용
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_MyPlayer(TEXT("AnimBlueprint'/Game/Blueprints/Local/Animations/ABP_MyPlayer.ABP_MyPlayer_C'"));
	if (ABP_MyPlayer.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(ABP_MyPlayer.Class);
	}

	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SetRelativeLocation(FVector(0, 46, 93));
	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	GetCharacterMovement()->CrouchedHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayer::Fire);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyPlayer::Crouching);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMyPlayer::Right);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPlayer::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyPlayer::Yaw);
}

void AMyPlayer::Fire()
{
}

void AMyPlayer::Forward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyPlayer::Right(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

//절대 회전을 변경함
void AMyPlayer::Pitch(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

//절대 회전을 변경함
void AMyPlayer::Yaw(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AMyPlayer::Crouching()
{
	CanCrouch() ? Crouch() : UnCrouch();
}
