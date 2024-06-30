// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PUPlayerController.h"

void APUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	bShowMouseCursor = true;
}

/// <summary>
/// 마우스가 가르키고 있는 위치를 반환
/// </summary>
/// <returns></returns>
FVector APUPlayerController::GetMousePos() 
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	return Hit.ImpactPoint;
}
