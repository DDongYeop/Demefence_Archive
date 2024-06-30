// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/PUCharacterEnemy.h"
#include <Components/CapsuleComponent.h>
#include "Character/Enemy/AI/PUAIController.h"
#include "Character/Player/PUCharacterPlayer.h"
#include <Kismet/GameplayStatics.h>

APUCharacterEnemy::APUCharacterEnemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PUEnemy"));

	AIControllerClass = APUAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ProjectU/Animation/Enemy/ABP_PUEnemy.ABP_PUEnemy_C"));
	if (AnimInstanceClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
}

void APUCharacterEnemy::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	APUCharacterPlayer* CharacterEnemy = Cast<APUCharacterPlayer>(Other);
	if (CharacterEnemy != nullptr)
	{
		CharacterEnemy->SetDamage(IDamage);
		UGameplayStatics::OpenLevel(this, "GameOver");
	}
}

void APUCharacterEnemy::CharacterDie()
{
	AActor::Destroy();
}
