// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSlotWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "Local/BDGameInstance.h"

void UItemSlotWidgetBase::NativeConstruct()
{
	ItemThumbnail = Cast<UImage>(GetWidgetFromName(TEXT("ItemThumbnail")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));

	ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));
	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UItemSlotWidgetBase::OnUseItem);
	}
}

FReply UItemSlotWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && !bEmpty)
	{
		UE_LOG(LogClass, Warning, TEXT("Item Right Click"));
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UItemSlotWidgetBase::OnUseItem()
{
	//UE_LOG(LogClass, Warning, TEXT("Use Item %d"), InventoryIndex);
	UBDGameInstance* GI = Cast<UBDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->UseItem(InventoryIndex);
	}
}

void UItemSlotWidgetBase::SetItemData(FItemDataTable ItemData)
{
	FStreamableManager Loader;
	UTexture2D* ItemTexture = Loader.LoadSynchronous<UTexture2D>(ItemData.ItemThumnail);
	if (ItemTexture)
	{
		ItemThumbnail->SetBrushFromTexture(ItemTexture);
	}
	ItemName->SetText(FText::FromString(ItemData.ItemName));
	ItemCount->SetText(FText::FromString(FString::FromInt(ItemData.ItemCount)));
	SetVisibility(ESlateVisibility::Visible);
	bEmpty = false;
}
