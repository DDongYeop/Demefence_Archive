// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PUCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include <Components/CapsuleComponent.h>

#include "Character/Player/Attack/PUProjectileActor.h"

APUCharacterPlayer::APUCharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName("PUPlayer");

	//Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ProjectU/Animation/Player/ABP_PUCharacter.ABP_PUCharacter_C"));
	if (AnimInstanceClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);

	//Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/ProjectU/Input/IMC_Default.IMC_Default"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Game/ProjectU/Input/IA_Jump.IA_Jump"));
	if (InputActionJumpRef.Object)
		MoveAction = InputActionJumpRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Game/ProjectU/Input/IA_Move.IA_Move"));
	if (InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Game/ProjectU/Input/IA_Look.IA_Look"));
	if (InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShiftRef(TEXT("/Game/ProjectU/Input/IA_Attack_Shift.IA_Attack_Shift"));
	if (InputActionShiftRef.Object)
		AttackShiftAction = InputActionShiftRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionERef(TEXT("/Game/ProjectU/Input/IA_Attack_E.IA_Attack_E"));
	if (InputActionERef.Object)
		AttackEAction = InputActionERef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQRef(TEXT("/Game/ProjectU/Input/IA_Attack_Q.IA_Attack_Q"));
	if (InputActionQRef.Object)
		AttackQAction = InputActionQRef.Object;
}

void APUCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	cPlayerController = Cast<APUPlayerController>(GetController());

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

	//Camera Position
	CameraBoom->TargetArmLength = 1250;
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 45.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;
}

void APUCharacterPlayer::Tick(float DeltaTime)
{
	Look();
}

void APUCharacterPlayer::CharacterDie()
{
}

void APUCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APUCharacterPlayer::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APUCharacterPlayer::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APUCharacterPlayer::Move);

	EnhancedInputComponent->BindAction(AttackShiftAction, ETriggerEvent::Triggered, this, &APUCharacterPlayer::AttackShift);
	EnhancedInputComponent->BindAction(AttackEAction, ETriggerEvent::Triggered, this, &APUCharacterPlayer::AttackE);
	EnhancedInputComponent->BindAction(AttackQAction, ETriggerEvent::Triggered, this, &APUCharacterPlayer::AttackQ);
}

void APUCharacterPlayer::Move(const FInputActionValue& Value)
{
	/*FVector2D MovementVector = Value.Get<FVector2D>();

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());

	AddMovementInput(MoveDirection, MovementVectorSize);*/

	FVector2D MovementVector = Value.Get<FVector2D>();
	MovementVector.Normalize();

	AddMovementInput(FVector(1, 1, 0), MovementVector.X);
	AddMovementInput(FVector(-1, 1, 0), MovementVector.Y);
}

void APUCharacterPlayer::Look()
{
	FVector Target = cPlayerController->GetMousePos();
	FVector Current = GetActorLocation();
	Target.Z = Current.Z = 0;

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Current, Target));
}

void APUCharacterPlayer::AttackShift(const FInputActionValue& Value)
{
	//투사체 공격

	APUProjectileActor* Projectile = GetWorld()->SpawnActor<APUProjectileActor>(ProjectileActor, GetActorLocation(), GetActorRotation());
	Projectile->FireInDirection(GetActorRotation().Vector());
}

void APUCharacterPlayer::AttackE(const FInputActionValue& Value)
{
	//범위 공격
}

void APUCharacterPlayer::AttackQ(const FInputActionValue& Value)
{
	//지키기 
}
