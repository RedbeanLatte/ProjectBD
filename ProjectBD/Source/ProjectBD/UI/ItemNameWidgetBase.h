// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemNameWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UItemNameWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextBlock* ItemName;

	virtual void NativeConstruct() override;
};
