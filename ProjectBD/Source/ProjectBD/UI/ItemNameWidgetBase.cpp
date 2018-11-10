// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemNameWidgetBase.h"
#include "Components/TextBlock.h"

void UItemNameWidgetBase::NativeConstruct()
{
	//블루프린트로 만든 위젯 인스턴스를 부모의 포인터 변수에 연결
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}