// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UExoTanksHUD;
class UButton;

/**
 * 
 */
UCLASS()
class EXOTANKS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

private:
	TObjectPtr<UExoTanksHUD> HUDWidget;

	//==== Widgets ====

	UPROPERTY(meta = (BindWidget));
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget));
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget));
	UButton* QuitButton;

private:
	//==== Natives ====

	virtual void NativeConstruct() override;


	//==== Event Handlers ====

	UFUNCTION()
	void PlayClicked();

	UFUNCTION()
	void OptionsClicked();

	UFUNCTION()
	void QuitClicked();
};
