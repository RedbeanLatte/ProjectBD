// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalPC.h"
#include "Local/MyPlayerCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemNameWidgetBase.h"
#include "UI/InventoryWidgetBase.h"
#include "Components/TextBlock.h"
#include "UI/InventoryWidgetBase.h"
#include "UI/ItemSlotWidgetBase.h"
#include "Local/BDGameInstance.h"
#include "Kismet/GameplayStatics.h"

ALocalPC::ALocalPC()
{
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass(); // COD 에 있는 Class를 참조해서 등록한 클래스를 생성
}

void ALocalPC::BeginPlay()
{
	// 블프 경로 저장
	FStringClassReference ItemNameClass(TEXT("WidgetBlueprint'/Game/Blueprints/UI/ItemNameWidget.ItemNameWidget_C'"));

	//블프 클래스 로딩(CDO)
	if (UClass* MyWidgetClass = ItemNameClass.TryLoadClass<UUserWidget>())
	{
		//로딩된 블프 클래스 갖고 인스턴스 생성, 붙이기
		ItemNameWidget = Cast<UItemNameWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		ItemNameWidget->AddToViewport();

		ItemNameWidget->ItemName->SetText(FText::FromString(TEXT("CPP로 만든 이름")));
		ItemNameWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	// 블프 경로 저장
	FStringClassReference InventoryClass(TEXT("WidgetBlueprint'/Game/Blueprints/UI/InventoryWidget.InventoryWidget_C'"));

	//블프 클래스 로딩(CDO)
	if (UClass* MyWidgetClass = InventoryClass.TryLoadClass<UUserWidget>())
	{
		//로딩된 블프 클래스 갖고 인스턴스 생성, 붙이기
		InventoryWidget = Cast<UInventoryWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ALocalPC::ShowItemName(FString & ItemName, bool Show)
{
	ItemNameWidget->ItemName->SetText(FText::FromString(ItemName));
	if (Show)
	{
		ItemNameWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemNameWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ALocalPC::ShowInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void ALocalPC::UpdateSlotData()
{
	InventoryWidget->HideAllSlot();

	UBDGameInstance* GI = Cast<UBDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		//for (int i = 0; i < GI->Inventory.Num(); i++)
		int i = 0;
		for (auto ItemData : GI->Inventory)
		{
			UItemSlotWidgetBase* Slot = InventoryWidget->GetEmptySlot();
			if (Slot)
			{
				Slot->SetItemData(ItemData);
				Slot->InventoryIndex = i;
			}
			i++;
			//빈 UI 슬롯이 없으면 아이템 그리지 않음
		}
	}
}
