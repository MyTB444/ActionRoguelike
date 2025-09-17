// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvTargetDummy.h"

// Sets default values
ATrvTargetDummy::ATrvTargetDummy()
{
 	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	TrvAttributeComponent = CreateDefaultSubobject<UTrvAttributeComponent>(TEXT("TrvAttributeComponent"));
	TrvAttributeComponent->OnHealthChange.AddDynamic(this, &ATrvTargetDummy::OnHealthChange);
}

void ATrvTargetDummy::OnHealthChange(AActor* Intistigator, UTrvAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0.0f){
		StaticMesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
}



