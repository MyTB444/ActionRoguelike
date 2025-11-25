// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrvAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, IntistigatorActor, UTrvAttributeComponent*,
                                              OwningComp, float, Newhealth, float, Delta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UTrvAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UTrvAttributeComponent* GetAttributes(AActor* FromActor);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* FromActor);
	
	UTrvAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;
	// Called when the game starts

public:
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);
	
	UFUNCTION(Blueprintable)
	bool Kill(AActor* Intistigator);

	// Called every frame
};
