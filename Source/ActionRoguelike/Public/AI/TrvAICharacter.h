// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "TrvAICharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ATrvAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrvAICharacter();

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* SensComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	
	// Called to bind functionality to input
};
