// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/AI/PUAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName APUAIController::Key_PlayerPos(TEXT("PlayerPos"));

APUAIController::APUAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/ProjectU/AI/BB_PUBlackBoard.BB_PUBlackBoard"));
	if (BBObject.Object)
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/ProjectU/AI/BT_PUBehaviorTree.BT_PUBehaviorTree"));
	if (BTObject.Object)
		BTAsset = BTObject.Object;
}

void APUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void APUAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BBAsset, BlackboardComp))
		RunBehaviorTree(BTAsset);
}

void APUAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComp)
		BehaviorTreeComp->StopTree(EBTStopMode::Safe);
}
