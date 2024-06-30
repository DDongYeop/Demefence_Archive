// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PUGameMode.h"
#include "Character/Player/PUPlayerController.h"

APUGameMode::APUGameMode()
{
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class)
	//	DefaultPawnClass = ThirdPersonClassRef.Class;

	//DefaultPawnClass
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ProjectU/Blueprint/Character/Player/BP_PUCharacterPlayer.BP_PUCharacterPlayer_C"));
	if (DefaultPawnClassRef.Class)
		DefaultPawnClass = DefaultPawnClassRef.Class;

	//PlayerControllerClass
	//PlayerControllerClass = APUPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ProjectU.PUPlayerController"));
	if (PlayerControllerClassRef.Class)
		PlayerControllerClass = PlayerControllerClassRef.Class;
}
