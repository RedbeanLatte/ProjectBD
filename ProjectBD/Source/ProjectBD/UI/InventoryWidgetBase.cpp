// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidgetBase.h"
#include "Components/ScrollBox.h"
#include "UI/ItemSlotWidgetBase.h"

void UInventoryWidgetBase::NativeConstruct()
{
	UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("InventoryScrollBox")));
	if (ScrollBox)
	{
		for (int i = 0; i < ScrollBox->GetChildrenCount(); i++)
		{
			if (UItemSlotWidgetBase* ItemSlot = Cast<UItemSlotWidgetBase>(ScrollBox->GetChildAt(i)))
			{
				Slots.Add(ItemSlot);
			}
		}
	}

	for (auto Slot : Slots)
	{
		Slot->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UItemSlotWidgetBase * UInventoryWidgetBase::GetEmptySlot()
{
	for (auto Slot : Slots)
	{
		if (Slot->bEmpty)
		{
			return Slot;
		}
	}

	return nullptr;
}

void UInventoryWidgetBase::HideAllSlot()
{
	for (auto Slot : Slots)
	{
		Slot->bEmpty = true;
		Slot->SetVisibility(ESlateVisibility::Collapsed);
	}
}
