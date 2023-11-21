// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	if (PlayButton)
		PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::PlayClicked);

	if (OptionsButton)
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OptionsClicked);

	if (QuitButton)
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::QuitClicked);
}

void UMainMenu::NativeDestruct()
{
	OnCloseCompleted.Clear();
}

void UMainMenu::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation == CloseMainMenuAnimation)
		OnCloseCompleted.Broadcast();
}

void UMainMenu::PlayClicked()
{
	if (!CloseMainMenuAnimation)
	{
		GLog->Log(ELogVerbosity::Error, "MainMenu : NativeConstruct() -> CloseMainMenuAnimation is null !");
		return;
	}

	PlayAnimation(CloseMainMenuAnimation);
}

void UMainMenu::OptionsClicked()
{
	GLog->Log("Options Clicked !");
}

void UMainMenu::QuitClicked()
{
	GLog->Log("Quit Clicked !");
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		EQuitPreference::Quit,
		false
	);
}
