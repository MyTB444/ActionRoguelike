// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrvAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "TrvTargetDummy.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ATrvTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrvTargetDummy();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UTrvAttributeComponent* TrvAttributeComponent;

	UFUNCTION()
	void OnHealthChange(AActor* Intistigator, UTrvAttributeComponent* OwningComp, float NewHealth, float Delta);
};
