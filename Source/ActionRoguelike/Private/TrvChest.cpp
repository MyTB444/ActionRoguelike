// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvChest.h"
// Sets default values
ATrvChest::ATrvChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.f;
}

// Called when the game starts or when spawned
void ATrvChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrvChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATrvChest::Interact_Implementation(APawn* Pawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

