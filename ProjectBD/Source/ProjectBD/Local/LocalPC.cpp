// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalPC.h"
#include "Local/MyPlayerCameraManager.h"

ALocalPC::ALocalPC()
{
	PlayerCameraManagerClass = AMyPlayerCameraManager::StaticClass(); // COD 에 있는 Class를 참조해서 등록한 클래스를 생성
}
