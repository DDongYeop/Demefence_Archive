// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UBTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTU_API UUBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UUBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
