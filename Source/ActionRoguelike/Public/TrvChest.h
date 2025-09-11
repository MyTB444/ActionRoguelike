// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrvGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "TrvChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ATrvChest : public AActor, public ITrvGameplayInterface
{
	GENERATED_BODY()
	void Interact_Implementation(APawn* Pawn);
public:	
	// Sets default values for this actor's properties
	ATrvChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
