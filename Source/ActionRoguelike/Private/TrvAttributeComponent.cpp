// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvAttributeComponent.h"

#include "TrvGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Damage multiplier enabled"), ECVF_Cheat);


// Sets default values for this component's properties
UTrvAttributeComponent::UTrvAttributeComponent()
{
	Health = 100;
	MaxHealth = 100;
	// ...
}

bool UTrvAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


// Called when the game starts


bool UTrvAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}
	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		
		Delta *= DamageMultiplier;
	}
	Health += Delta;

	OnHealthChange.Broadcast(InstigatorActor, this, Health, Delta);
	
	if (Delta < 0.0f && Health == 0.0f)
	{
		ATrvGameModeBase* GM = GetWorld()->GetAuthGameMode<ATrvGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	} 

	return true;
}

bool UTrvAttributeComponent::Kill(AActor* Intistigator)
{
	return ApplyHealthChange(Intistigator, -MaxHealth);
}

UTrvAttributeComponent* UTrvAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UTrvAttributeComponent>(FromActor->GetComponentByClass(UTrvAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UTrvAttributeComponent::IsActorAlive(AActor* FromActor)
{
	UTrvAttributeComponent* AttributeComponent = GetAttributes(FromActor);
	if (AttributeComponent)
	{
		return AttributeComponent->IsAlive();
	}
	return false;
}


// Called every frame
