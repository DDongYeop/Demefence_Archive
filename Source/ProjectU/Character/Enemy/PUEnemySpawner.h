// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PUEnemySpawner.generated.h"

UCLASS()
class PROJECTU_API APUEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APUEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void EnemySpawn();

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float fSpawnTime;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<FVector> SpawnPos;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class APUCharacterEnemy> Enemy;
	

private:
	float fCurrentTime;
};
