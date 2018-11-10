// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Items/ItemComponent.h"
#include "Engine/StreamableManager.h"
#include "Local/MyPlayer.h"

// Sets default values
AMasterItem::AMasterItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetSphereRadius(150.0f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	Item = CreateDefaultSubobject<UItemComponent>(TEXT("Item"));
}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (Item->ItemDataTable)
	{
		ItemIndex = FMath::RandRange(1, 6);
		ItemData = Item->GetItemData(ItemIndex * 10);

		FStreamableManager Loader;
		StaticMesh->SetStaticMesh(Loader.LoadSynchronous<UStaticMesh>(ItemData.ItemMesh));
	}

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMasterItem::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMasterItem::EndOverlap);
}

void AMasterItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Player->AddItemList(this);
		}
	}
}

void AMasterItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Player->RemoveItemList(this);
		}
	}
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

