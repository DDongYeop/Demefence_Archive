// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTU_API APUPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

//Attack Section
public:
	FVector GetMousePos();
};
