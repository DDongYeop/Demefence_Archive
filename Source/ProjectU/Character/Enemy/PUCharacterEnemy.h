// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PUCharacterBase.h"
#include "PUCharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTU_API APUCharacterEnemy : public APUCharacterBase
{
	GENERATED_BODY()
	
public:
	APUCharacterEnemy();

protected:
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	virtual void CharacterDie() override;

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	int IDamage;
};
