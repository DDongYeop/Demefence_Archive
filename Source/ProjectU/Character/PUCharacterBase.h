// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUCharacterBase.generated.h"

UCLASS()
class PROJECTU_API APUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APUCharacterBase();

private:
	UPROPERTY(EditAnywhere, Category = "Character")
	int iMaxHp;

	int iCurrentHp;

public:
	void SetDamage(int Damage);

protected:
	virtual void CharacterDie();

public:
	int GetMaxHp() { return iMaxHp; };
	int GetCurrentHp() { return iCurrentHp; };
};
