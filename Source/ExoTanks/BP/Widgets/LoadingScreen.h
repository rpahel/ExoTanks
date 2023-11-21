// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadingScreenDelegate);

/**
 * 
 */
UCLASS()
class EXOTANKS_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FLoadingScreenDelegate OnLoadingComplete;

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* LoadingBarAnimation;

private:
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
