// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvInteractionComponent.h"

#include "CollisionDebugDrawingPublic.h"
#include "TrvGameplayInterface.h"
#include "Concepts/Iterable.h"
#include "ProfilingDebugging/CookStats.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(
	TEXT("su.DebugDrawInteraction"), false, TEXT("Enable debug lines"), ECVF_Cheat);

// Sets default values for this component's properties
UTrvInteractionComponent::UTrvInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTrvInteractionComponent::PrimaryInteraction()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	//FHitResult Hit;
	//bool bLocking = GetWorld()->LineTraceSingleByObjectType(Hit ,EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(30.0f);

	bool bLocking = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams,
	                                                   Shape);

	FColor Color = bLocking ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32, Color, false, 2.0f);
		}
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UTrvGameplayInterface>())
			{
				APawn* Pawn = Cast<APawn>(Owner);
				ITrvGameplayInterface::Execute_Interact(HitActor, Pawn);
				break;
			}
		}
	}
	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, Color, false, 2.0f, 0, 2.0f);
	}
}

void UTrvInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTrvInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
