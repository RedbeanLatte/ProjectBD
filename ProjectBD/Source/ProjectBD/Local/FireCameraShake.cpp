// Fill out your copyright notice in the Description page of Project Settings.

#include "FireCameraShake.h"

UFireCameraShake::UFireCameraShake()
{
	OscillationDuration = 0.05f;
	OscillationBlendInTime = 0.02f;
	OscillationBlendOutTime = 0.02f;

	RotOscillation.Pitch.Amplitude = 15.0f;
	RotOscillation.Pitch.Frequency = 1.0f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
}
