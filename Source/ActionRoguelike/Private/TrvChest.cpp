// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvChest.h"
// Sets default values
ATrvChest::ATrvChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.f;
}

// Called when the game starts or when spawned

void ATrvChest::Interact_Implementation(APawn* Pawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
