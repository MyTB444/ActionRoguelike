// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrvAttributeComponent.h"
#include "TRVWorldUserWidget.h"
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
	
	UPROPERTY()
	UTRVWorldUserWidget* ActiveHealthBar;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* SensComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTrvAttributeComponent* AttributeComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	FName TimeToHitParamName;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	
	UFUNCTION()
	void OnHealthChange(AActor* Intistigator, UTrvAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	void SetTargetActor(AActor* TargetActor);
	
	// Called to bind functionality to input
};
