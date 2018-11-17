// Fill out your copyright notice in the Description page of Project Settings.

#include "BDGameInstance.h"
#include "Items/ItemDataTable.h"
#include "Local/LocalPC.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

bool UBDGameInstance::PushItem(FItemDataTable Item)
{
	//소비형 아이템
	if (Item.ItemType == EItemType::Consume)
	{
		//동일 아이템 슬롯에 갯수 늘리기
		int Index = GetSameSlotIndexByItemIndex(Item);
		if (Index != -1)
		{
			Inventory[Index].ItemCount += Item.ItemCount;
		}
		else
		{
			//신규 아이템 추가
			Inventory.Add(Item);
		}
		return true;
	}
	//장비하는 아이템
	else if (Item.ItemType == EItemType::Equip)
	{
		//무작정 추가
		Inventory.Add(Item);
		return true;
	}
	
	return false;
}

bool UBDGameInstance::UseItem(int Index)
{
	if (Inventory[Index].ItemType == EItemType::Consume)
	{
		//사용 삭제
		//에너지 회복
		Inventory[Index].ItemCount--;
		if (Inventory[Index].ItemCount == 0)
		{
			Inventory.RemoveAt(Index);
		}
	}
	else
	{
		//장착
		UE_LOG(LogClass, Warning, TEXT("장착"));
	}

	//아이템 사용 후 UI 업데이트
	ALocalPC* PC = Cast<ALocalPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->UpdateSlotData();
	}

	return true;
}

int UBDGameInstance::GetSameSlotIndexByItemIndex(FItemDataTable Data)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemIndex == Data.ItemIndex)
		{
			return i;
		}
	}

	return -1;
}