// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvAICharacter.h"

#include "Perception/AIPerceptionComponent.h"

// Sets default values
ATrvAICharacter::ATrvAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
}

// Called when the game starts or when spawned
void ATrvAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrvAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
