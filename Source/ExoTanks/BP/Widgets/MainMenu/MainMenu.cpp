// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::NativeConstruct()
{
	if (PlayButton)
		PlayButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::PlayClicked);

	if (OptionsButton)
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::OptionsClicked);

	if (QuitButton)
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenu::QuitClicked);
}

void UMainMenu::PlayClicked()
{
	GLog->Log("Play Clicked !");
}

void UMainMenu::OptionsClicked()
{
	GLog->Log("Options Clicked !");
}

void UMainMenu::QuitClicked()
{
	GLog->Log("Quit Clicked !");
}
