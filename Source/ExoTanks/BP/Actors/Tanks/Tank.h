// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class UBoxComponent;
class AProjectile;

UCLASS(Abstract, NotBlueprintable)
class EXOTANKS_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	//==== Exposed Fields ====
	
	UPROPERTY(EditDefaultsOnly)
	FVector2D CannonRotationRange = FVector2D(-10, 50);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> Projectile;

	//==== Components ====
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* PawnMovement;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollider; // Pour les mouvements

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider; // Pour les collisions

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BodyPivot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* TurretPivot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CannonPivot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CannonMesh;

public:
	ATank();
	FRotator GetTurretRotator() const;
	void Shoot();
};
