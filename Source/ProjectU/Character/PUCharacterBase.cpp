// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PUCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APUCharacterBase::APUCharacterBase()
{
    //Pawn
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    //Movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = .35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    //Mesh
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM"));
    if (CharacterMeshRef.Object)
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
}

void APUCharacterBase::SetDamage(int Damage)
{
    iCurrentHp -= Damage;

    if (iCurrentHp <= 0)
        CharacterDie();
}

void APUCharacterBase::CharacterDie()
{
    UE_LOG(LogTemp, Log, TEXT("Die"));
}
