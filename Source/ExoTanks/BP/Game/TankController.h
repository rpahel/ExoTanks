// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerTank;

/**
 * 
 */
UCLASS()
class EXOTANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
private:
	//==== Exposed Fields ====

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Values")
	float MouseSensitivity = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* TankMovement;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* TankLook;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* Shoot;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* Aim;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UInputAction* Quit;

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

	UFUNCTION()
	void TankMovementHandler(const FInputActionValue& Value);

	UFUNCTION()
	void TankAimStart(const FInputActionValue& Value);

	UFUNCTION()
	void TankAimComplete(const FInputActionValue& Value);

	UFUNCTION()
	void TankShoot(const FInputActionValue& Value);

	UFUNCTION()
	void QuitPressed(const FInputActionValue& Value);
};
