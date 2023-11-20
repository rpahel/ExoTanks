// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ExoTanks/BP/Actors/Projectile.h"

#pragma region Public
ATank::ATank()
{
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	if (!PawnMovement)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> PawnMovement is null !");
		return;
	}

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	if (!SphereCollider)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> SphereCollider is null !");
		return;
	}
	SetRootComponent(SphereCollider);

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
	if (!TurretPivot)
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

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	if (!ProjectileSpawnPoint)
	{
		GLog->Log(ELogVerbosity::Error, GetName() + " : Constructor -> ProjectileSpawnPoint is null !");
		return;
	}
	ProjectileSpawnPoint->SetupAttachment(CannonPivot);
}

FRotator ATank::GetTurretRotator() const
{
	return TurretPivot->GetRelativeRotation();
}

void ATank::Shoot()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;

	FTransform transform;
	transform.SetLocation(ProjectileSpawnPoint->GetComponentLocation());
	transform.SetRotation(ProjectileSpawnPoint->GetComponentRotation().Quaternion());

	GetWorld()->SpawnActor(
		Projectile,
		&transform,
		SpawnInfo);
}
#pragma endregion