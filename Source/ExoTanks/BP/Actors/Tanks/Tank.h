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

	//==== Fields ====

	UPROPERTY(EditAnywhere)
	float MaxFuel = 100.f;

	UPROPERTY(EditAnywhere)
	float FuelDrainSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float FuelGainSpeed = 1.f;
	
	float CurrentFuel;
	float DeltaTime;

	bool IsMoving = false;

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

	virtual void Tick(float DeltaSeconds) override;

	void SetIsMoving(const bool bIsMoving);
	void Shoot();
	void MoveTowards(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false);
	FRotator GetTurretRotator() const;
};
