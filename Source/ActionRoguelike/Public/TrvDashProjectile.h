// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrvProjectileBase.h"
#include "TrvDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ATrvDashProjectile : public ATrvProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	FVector ThisLocation;
	FTimerHandle TimerHandle;
	UFUNCTION()
	void DestroyTime();
	virtual void Explode_Implementation() override;
	void TpGideon();
	
};
