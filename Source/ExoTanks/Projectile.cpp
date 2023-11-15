// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

AProjectile::AProjectile()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	if (!BoxComponent)
	{
		GLog->Log(ELogVerbosity::Error, "Projectile : Constructor -> BoxComponent is null !");
		return;
	}
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if (!StaticMeshComponent)
	{
		GLog->Log(ELogVerbosity::Error, "Projectile : Constructor -> StaticMeshComponent is null !");
		return;
	}
	StaticMeshComponent->SetupAttachment(BoxComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	if (!ProjectileMovementComponent)
	{
		GLog->Log(ELogVerbosity::Error, "Projectile : Constructor -> ProjectileMovementComponent is null !");
		return;
	}
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (PossibleVisuals.Num() > 0)
	{
		TObjectPtr<UStaticMesh> mesh = PossibleVisuals[FMath::RandHelper(PossibleVisuals.Num())];
		
		if(mesh)
			StaticMeshComponent->SetStaticMesh(PossibleVisuals[FMath::RandHelper(PossibleVisuals.Num())]);
	}
}
