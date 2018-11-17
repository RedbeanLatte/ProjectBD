// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Items/ItemDataTable.h"
#include "BDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UBDGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	TArray<FItemDataTable> Inventory;

	bool PushItem(FItemDataTable Item);
	bool UseItem(int Index);
	int GetSameSlotIndexByItemIndex(FItemDataTable Data);
};
