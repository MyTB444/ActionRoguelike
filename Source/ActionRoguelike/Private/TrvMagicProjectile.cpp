// Fill out your copyright notice in the Description page of Project Settings.

#include "TrvMagicProjectile.h"
#include "TrvAttributeComponent.h"
#include "TrvGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"


// Sets default values
ATrvMagicProjectile::ATrvMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrvMagicProjectile::OnActorOverlap);
	DamageAmount = 20.0f;
}

void ATrvMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (UTrvGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(),OtherActor,DamageAmount,SweepResult))
		{
			Explode();
		}
	}
}
