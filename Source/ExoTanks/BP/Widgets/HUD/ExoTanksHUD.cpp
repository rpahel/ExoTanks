// Fill out your copyright notice in the Description page of Project Settings.


#include "ExoTanksHUD.h"
#include "Components/CanvasPanelSlot.h"
#include "ExoTanks/BP/Widgets/MainMenu/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "ExoTanks/BP/Game/TankController.h"

void UExoTanksHUD::Play()
{
	if (MainMenu)
		MainMenu->SetVisibility(ESlateVisibility::Collapsed);
}

void UExoTanksHUD::NativeConstruct()
{
	Controller = Cast<ATankController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (Controller)
	{
		Controller->SetShowMouseCursor(true);
		Controller->SetInputMode(FInputModeUIOnly());
		Controller->bEnableClickEvents = true;
		Controller->bEnableMouseOverEvents = true;
	}

	if (!MainMenu)
	{
		if (!W_MainMenu)
		{
			GLog->Log(ELogVerbosity::Error, "ExoTanksHUD : NativeConstruct() -> W_MainMenu is null !");
			return;
		}

		MainMenu = Cast<UMainMenu>(CreateWidget(this, W_MainMenu, FName("MainMenu")));


		if (!MainMenu)
		{
			GLog->Log(ELogVerbosity::Error, "ExoTanksHUD : NativeConstruct() -> Something went wrong went creating MainMenu widget !");
			return;
		}

		GLog->Log(ELogVerbosity::Log, "ExoTanksHUD : NativeConstruct() -> MainMenu Created !");

		AddToCanvas(MainMenu);
	}
}

void UExoTanksHUD::AddToCanvas(TObjectPtr<UUserWidget> WidgetToFit)
{
	if (!WidgetToFit)
		return;

	WidgetToFit->AddToViewport(1);

	TObjectPtr<UCanvasPanelSlot> CanvasSlot = Cast<UCanvasPanelSlot>(WidgetToFit->Slot);

	if (!CanvasSlot)
		return;

	CanvasSlot->SetAnchors(FAnchors(0.f));
}
