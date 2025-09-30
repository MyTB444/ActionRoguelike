// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TrvBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ATrvBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrvBarrel();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* RadialForceComponent;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent,
	                AActor* OtherActor,
	                UPrimitiveComponent* OtherComp,
	                FVector NormalImpulse,
	                const FHitResult& Hit);

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
