// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ATrvDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("RadialForceComponent"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATrvDashProjectile::DestroyTime, 0.2f, false);
}

void ATrvDashProjectile::TpGideon()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		// Keep instigator rotation or it may end up jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

void ATrvDashProjectile::DestroyTime()
{
	ThisLocation = GetActorLocation();
	Explode();
}

void ATrvDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle2;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ATrvDashProjectile::TpGideon, 0.2f, false);
	//Super::Explode_Implementation();
}
