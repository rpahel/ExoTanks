// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreen.h"

void ULoadingScreen::NativeConstruct()
{
	if (!LoadingBarAnimation)
	{
		GLog->Log(ELogVerbosity::Error, "LoadingScreen : NativeConstruct() -> LoadingBarAnimation is null !");
		return;
	}

	PlayAnimation(LoadingBarAnimation);
}

void ULoadingScreen::NativeDestruct()
{
	OnLoadingComplete.Clear();
}

void ULoadingScreen::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation == LoadingBarAnimation)
		OnLoadingComplete.Broadcast();
}
