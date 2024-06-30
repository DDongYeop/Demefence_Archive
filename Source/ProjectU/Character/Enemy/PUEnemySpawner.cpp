// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/PUEnemySpawner.h"
#include "Character/Enemy/PUCharacterEnemy.h"
#include <time.h>

// Sets default values
APUEnemySpawner::APUEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APUEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APUEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	fCurrentTime += DeltaTime;

	if (fCurrentTime >= fSpawnTime)
		EnemySpawn();
}

void APUEnemySpawner::EnemySpawn()
{
	fCurrentTime -= fSpawnTime;
	fSpawnTime -= fSpawnTime * .001f;

	// ½ºÆù 
	int num = rand() % SpawnPos.Num();
	GetWorld()->SpawnActor<APUCharacterEnemy>(Enemy, SpawnPos[num], GetActorRotation());
}
