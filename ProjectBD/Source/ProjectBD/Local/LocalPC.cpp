// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalPC.h"
#include "Local/MyPlayerCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemNameWidgetBase.h"
#include "Components/TextBlock.h"

ALocalPC::ALocalPC()
{
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass(); // COD 에 있는 Class를 참조해서 등록한 클래스를 생성
}

void ALocalPC::BeginPlay()
{
	// 블프 경로 저장
	FStringClassReference ItemNameClass(TEXT("WidgetBlueprint'/Game/Blueprints/UI/ItemNameWidget.ItemNameWidget_C'"));

	//블프 클래스 로딩
	if (UClass* MyWidgetClass = ItemNameClass.TryLoadClass<UUserWidget>())
	{
		//로딩된 블프 클래스 갖고 인스턴스 생성, 붙이기
		ItemNameWidget = Cast<UItemNameWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));
		ItemNameWidget->AddToViewport();

		ItemNameWidget->ItemName->SetText(FText::FromString(TEXT("CPP로 만든 이름")));
		ItemNameWidget->SetVisibility(ESlateVisibility::Collapsed);
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
