// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "TrvProjectileBase.h"
#include "TrvMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ATrvMagicProjectile : public ATrvProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrvMagicProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
