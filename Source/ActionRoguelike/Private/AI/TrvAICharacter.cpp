// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvAICharacter.h"

#include "AI/TrvAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ATrvAICharacter::ATrvAICharacter()
{
	SensComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensComp"));
}

void ATrvAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensComp->OnSeePawn.AddDynamic(this, &ATrvAICharacter::OnPawnSeen);
}

void ATrvAICharacter::OnPawnSeen(APawn* Pawn)
{
	ATrvAIController* AIC = Cast<ATrvAIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBC = AIC->GetBlackboardComponent();
		BBC->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(),"PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}


// Called to bind functionality to input
