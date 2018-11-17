// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemDataTable.h"
#include "ItemSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UItemSlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	class UImage* ItemThumbnail;
	class UTextBlock* ItemName;
	class UTextBlock* ItemCount;
	class UButton* ItemButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bEmpty = true;

	UFUNCTION(BlueprintCallable)
	void SetItemData(FItemDataTable ItemData);

	UFUNCTION()
	void OnUseItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int InventoryIndex = -1;
};
