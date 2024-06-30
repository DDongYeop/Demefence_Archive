// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/AI/UBTService_Detect.h"
#include "PUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTService_Detect::UUBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UUBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn == nullptr)
	{
		int i = 0;
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(APUAIController::Key_PlayerPos, PlayerPawn->GetActorLocation());
}
