// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LocalPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API ALocalPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALocalPC();
	
	virtual void BeginPlay() override;
	
	class UItemNameWidgetBase* ItemNameWidget;
	class UInventoryWidgetBase* InventoryWidget;

	void ShowItemName(FString& ItemName, bool Show = true);

	void ShowInventory();
	void UpdateSlotData();
};
