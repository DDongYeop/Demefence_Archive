// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PUAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPUAnimInstance::UPUAnimInstance()
{
	MovingThreshould = 3.f;
	JumpingThreshould = 100.f;
}

void UPUAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
		Movement = Owner->GetCharacterMovement();
}

void UPUAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); //XY�� �̿��ϸ� ������ �ӵ� ���� �� ����
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}
