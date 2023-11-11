// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tanks/PlayerTank.h"
#include "TankController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class EXOTANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
private:
	//==== Exposed Fields ====

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* TankMovement;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* TankLook;

	//==== Fields ====
	UPROPERTY()
	APlayerTank* PlayerTank;

private:
	//==== Overrides ====

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	//==== Event Handlers ====

	UFUNCTION()
	void TankLookHandler(const FInputActionValue& Value);
};
