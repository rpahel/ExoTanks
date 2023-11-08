// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#pragma region Public
ATank::ATank()
{
	TObjectPtr<USceneComponent> newRoot = CreateDefaultSubobject<USceneComponent>("Root");
	if (!newRoot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> newRoot is null !");
		return;
	}
	SetRootComponent(newRoot);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	if (!BoxCollider)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> BoxCollider is null !");
		return;
	}
	BoxCollider->SetupAttachment(GetRootComponent());

	BodyPivot = CreateDefaultSubobject<USceneComponent>("BodyPivot");
	if (!BodyPivot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> BodyPivot is null !");
		return;
	}
	BodyPivot->SetupAttachment(GetRootComponent());

	TurretPivot = CreateDefaultSubobject<USceneComponent>("TurretPivot");
	if (!BoxCollider)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> TurretPivot is null !");
		return;
	}
	TurretPivot->SetupAttachment(GetRootComponent());

	CannonPivot = CreateDefaultSubobject<USceneComponent>("CannonPivot");
	if (!CannonPivot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> CannonPivot is null !");
		return;
	}
	CannonPivot->SetupAttachment(GetRootComponent());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
#pragma endregion

#pragma region Overrides
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	if (!BoxCollider)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : BeginPlay() -> BoxCollider is null !");
		Destroy();
		return;
	}

	if (!BodyPivot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : BeginPlay() -> BodyPivot is null !");
		Destroy();
		return;
	}

	if (!TurretPivot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : BeginPlay() -> TurretPivot is null !");
		Destroy();
		return;
	}

	if (!CannonPivot)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : BeginPlay() -> CannonPivot is null !");
		Destroy();
		return;
	}
}
#pragma endregion