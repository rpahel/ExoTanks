// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExoTanksHUD.generated.h"

class ATankController;
class ULoadingScreen;
class UMainMenu;

/**
 * 
 */
UCLASS()
class EXOTANKS_API UExoTanksHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	//==== Exposed Fields ====

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> W_LoadingScreen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> W_MainMenu;

	//==== Fields ====

	TObjectPtr<ATankController> Controller;
	TObjectPtr<ULoadingScreen> LoadingScreen;
	TObjectPtr<UMainMenu> MainMenu;

public:
	void Play();

private:
	//==== Natives ====

	virtual void NativeConstruct() override;

	//==== Methods ====

	void AddToCanvas(TObjectPtr<UUserWidget> WidgetToFit);
	TObjectPtr<UUserWidget> CreateAndAddWidget(TSubclassOf<UUserWidget> Widget);

	//==== Event Handlers ====
	
	UFUNCTION()
	void LoadingScreenToMainMenu();

	UFUNCTION()
	void SwitchToGameMode();

	UFUNCTION()
	void SwitchToUIMode();

	UFUNCTION()
	void KillMainMenu();
};