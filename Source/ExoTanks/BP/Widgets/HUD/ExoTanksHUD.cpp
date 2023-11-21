// Fill out your copyright notice in the Description page of Project Settings.


#include "ExoTanksHUD.h"
#include "Components/CanvasPanelSlot.h"
#include "ExoTanks/BP/Widgets/MainMenu/MainMenu.h"
#include "ExoTanks/BP/Widgets/LoadingScreen.h"
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
	SwitchToUIMode();

	LoadingScreen = Cast<ULoadingScreen>(CreateAndAddWidget(W_LoadingScreen));
	if (!LoadingScreen)
	{
		GLog->Log(ELogVerbosity::Error, "ExoTanksHUD : NativeConstruct() -> loadingScreen is null !");
		return;
	}
	LoadingScreen->OnLoadingComplete.AddUniqueDynamic(this, &UExoTanksHUD::LoadingScreenToMainMenu);
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

TObjectPtr<UUserWidget> UExoTanksHUD::CreateAndAddWidget(TSubclassOf<UUserWidget> Widget)
{
	TObjectPtr<UUserWidget> newWidget = nullptr;
	if (!Widget)
	{
		GLog->Log(ELogVerbosity::Error, "ExoTanksHUD : CreateAndAddWidget() -> Widget is null !");
		return nullptr;
	}

	newWidget = CreateWidget(this, Widget);

	if (!newWidget)
	{
		GLog->Log(ELogVerbosity::Error, "ExoTanksHUD : CreateMainMenuWidget() -> Something went wrong went creating newWidget !");
		return nullptr;
	}

	AddToCanvas(newWidget);

	return newWidget;
}

void UExoTanksHUD::LoadingScreenToMainMenu()
{
	MainMenu = Cast<UMainMenu>(CreateAndAddWidget(W_MainMenu));

	MainMenu->OnCloseCompleted.AddUniqueDynamic(this, &UExoTanksHUD::SwitchToGameMode);
	MainMenu->OnCloseCompleted.AddUniqueDynamic(this, &UExoTanksHUD::KillMainMenu);

	if (LoadingScreen)
		LoadingScreen->RemoveFromParent();
}

void UExoTanksHUD::SwitchToGameMode()
{
	if (Controller)
	{
		Controller->SetShowMouseCursor(false);
		Controller->SetInputMode(FInputModeGameOnly());
	}
}

void UExoTanksHUD::SwitchToUIMode()
{
	if (Controller)
	{
		Controller->SetShowMouseCursor(true);
		Controller->SetInputMode(FInputModeUIOnly());
		Controller->bEnableClickEvents = true;
		Controller->bEnableMouseOverEvents = true;
	}
}

void UExoTanksHUD::KillMainMenu()
{
	if (MainMenu)
		MainMenu->RemoveFromParent();
}
