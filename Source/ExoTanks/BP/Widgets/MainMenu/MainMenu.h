// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UExoTanksHUD;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMainMenuDelegate);

/**
 * 
 */
UCLASS()
class EXOTANKS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FMainMenuDelegate OnCloseCompleted;

private:
	TObjectPtr<UExoTanksHUD> HUDWidget;

	//==== Widgets ====

	UPROPERTY(meta = (BindWidget));
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget));
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget));
	UButton* QuitButton;


	//==== Widget Animations ====

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* CloseMainMenuAnimation;

private:
	//==== Natives ====

	virtual void NativeConstruct() override;
	virtual void NativeDestruct();
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;


	//==== Event Handlers ====

	UFUNCTION()
	void PlayClicked();

	UFUNCTION()
	void OptionsClicked();

	UFUNCTION()
	void QuitClicked();
};
