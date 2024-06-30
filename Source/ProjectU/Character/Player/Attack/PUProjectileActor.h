#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "PUProjectileActor.generated.h"

UCLASS()
class PROJECTU_API APUProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APUProjectileActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
public:
	void FireInDirection(const FVector& ShootDirection);

protected:
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); 

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UPROPERTY(EditAnywhere, Category = "Damage")
	int IDamage;

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TSubclassOf<AActor> ShotSound;
};
