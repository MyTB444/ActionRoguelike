// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvAttributeComponent.h"

// Sets default values for this component's properties
UTrvAttributeComponent::UTrvAttributeComponent()
{

	Health = 100;
	// ...
}

bool UTrvAttributeComponent::IsAlive () const
{
	return Health > 0.0f;
}


// Called when the game starts


bool UTrvAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChange.Broadcast(nullptr, this, Health, Delta);
	
	return true;
}


// Called every frame


