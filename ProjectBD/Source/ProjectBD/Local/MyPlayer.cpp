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
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

	//Camera 위치 저장
	NormalSpringArmPosition = SpringArm->GetRelativeTransform().GetLocation();
	CrouchSpringArmPosition = FVector(NormalSpringArmPosition.X, 
		NormalSpringArmPosition.Y, 
		NormalSpringArmPosition.Z - 40);
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

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyPlayer::Crouching);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &AMyPlayer::DoIronsight);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyPlayer::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyPlayer::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayer::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyPlayer::StopFire);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMyPlayer::Right);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPlayer::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyPlayer::Yaw);
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
	if (Value != 0.0f && !bIsSprint)
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
	if (bIsSprint)
	{
		return;
	}

	CanCrouch() ? Crouch() : UnCrouch();
}

void AMyPlayer::DoIronsight()
{
	if (bIsSprint) 
	{
		return;
	}

	bIsIronsight = bIsIronsight ? false : true;

	if (bIsIronsight && !bIsCrouched) 
	{
		GetCharacterMovement()->MaxWalkSpeed = IronsightSpeed;
	}
	else if (!bIsIronsight && !bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}
}

void AMyPlayer::StartSprint()
{
	if (bIsCrouched || bIsIronsight)
	{
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprint = true;
}

void AMyPlayer::StopSprint()
{
	if (bIsSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}

	bIsSprint = false;
}

FRotator AMyPlayer::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();
	return AimRotLS;
}

void AMyPlayer::StartFire()
{
	if (bIsSprint)
	{
		return;
	}

	bIsFire = true;
	OnShoot();
}

void AMyPlayer::StopFire()
{
	bIsFire = false;
}

void AMyPlayer::OnShoot()
{
	if (!bIsFire)
	{
		return;
	}

	//총알 계산
	//1. 카메라 위치, 회전
	FVector CameraLocation;
	FRotator CameraRotation;
	//AI or Player
	//GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//Local PlayerController 가져오기
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//2. 크로스 헤어 위치(화면 가운데 좌표)
	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	//3. 화면좌표 -> World 좌표 변환, Project(3D->2D), DeProject(2D->3D)
	//화면 가운데 위치를 3차원 월드 좌표로 변환
	FVector WorldLocation;
	FVector WorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(
		SizeX / 2,
		SizeY / 2,
		WorldLocation,
		WorldDirection
	);

	//4. 선을 만들어서 충돌체크(Camera부터 화면 가운데점을 지나는 선을 늘여서 충돌 체크)
	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (WorldDirection * 8000000.0f);

	//충돌할 물체 종류
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	//충돌 제외 리스트
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	FHitResult OutHit;

	bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		TraceStart,
		TraceEnd,
		ObjectTypes,
		true,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		3.0f
	);

	if (bResult)
	{
		UE_LOG(LogProjectBD, Warning, TEXT("Hit %s"), *OutHit.GetActor()->GetName());
	}


	//연사 구현
	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(ShootTimer, this, &AMyPlayer::OnShoot, 0.2f);
	}
}
