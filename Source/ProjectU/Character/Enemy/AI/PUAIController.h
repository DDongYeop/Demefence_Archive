// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PUAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTU_API APUAIController : public AAIController
{
	GENERATED_BODY()

public:
	APUAIController();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

public:
	static const FName Key_PlayerPos;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
