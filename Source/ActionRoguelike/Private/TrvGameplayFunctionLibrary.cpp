// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvGameplayFunctionLibrary.h"

#include "TrvAttributeComponent.h"

bool UTrvGameplayFunctionLibrary::ApplyDamage(AActor* Causer, AActor* Target, float Damage)
{
	UTrvAttributeComponent* AttributeComponent = UTrvAttributeComponent::GetAttributes(Target);
	if (AttributeComponent)
	{
		return AttributeComponent->ApplyHealthChange(Causer, -Damage);
	}
	return false;
}

bool UTrvGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* Causer, AActor* Target, float Damage,
	const FHitResult& HitResult)
{
	if (ApplyDamage(Causer, Target, Damage))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}
