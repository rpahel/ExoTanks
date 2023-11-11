// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#pragma region Public
ATank::ATank()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	if (!Root)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> RootComponent is null !");
		return;
	}
	SetRootComponent(Root);

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
	CannonPivot->SetupAttachment(TurretPivot);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	if (!BodyMesh)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> BodyMesh is null !");
		return;
	}
	BodyMesh->SetupAttachment(BodyPivot);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	if (!TurretMesh)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> TurretMesh is null !");
		return;
	}
	TurretMesh->SetupAttachment(TurretPivot);

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>("CannonMesh");
	if (!CannonMesh)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> CannonMesh is null !");
		return;
	}
	CannonMesh->SetupAttachment(CannonPivot);
}

//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
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