// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrvGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UTrvGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDamage(AActor* Causer, AActor* Target, float Damage);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDirectionalDamage(AActor* Causer, AActor* Target, float Damage, const FHitResult& HitResult);

};
