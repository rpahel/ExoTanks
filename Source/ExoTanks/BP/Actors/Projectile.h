// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class EXOTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:
	//==== Exposed Fields ====

	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> PossibleVisuals;

	//==== Components ====

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	AProjectile();

private:
	virtual void BeginPlay() override;
};
