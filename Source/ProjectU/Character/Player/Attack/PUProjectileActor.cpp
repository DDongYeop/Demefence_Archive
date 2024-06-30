// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/Attack/PUProjectileActor.h"
#include "Character/Enemy/PUCharacterEnemy.h"

// Sets default values
APUProjectileActor::APUProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName("PUAttack");
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = 3000.0f;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void APUProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ShotSound);
}

// Called every frame
void APUProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector CurrentLocation = GetActorLocation();
	//CurrentLocation += GetActorForwardVector() * fSpeed * DeltaTime;
	//SetActorLocation(CurrentLocation);
}

void APUProjectileActor::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void APUProjectileActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	APUCharacterEnemy* CharacterEnemy = Cast<APUCharacterEnemy>(Other);
	if (CharacterEnemy != nullptr)
	{
		CharacterEnemy->SetDamage(IDamage);
	}

	Destroy();
}
