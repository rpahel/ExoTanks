// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Tank.generated.h"

UCLASS(Abstract, NotBlueprintable)
class EXOTANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	//==== Components ====

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BodyPivot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* TurretPivot;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CannonPivot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CannonMesh;

public:
	ATank();

	//==== Overrides ====

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//==== Overrides ====

	virtual void BeginPlay() override;

//private:
//	//==== Methods ====
};
