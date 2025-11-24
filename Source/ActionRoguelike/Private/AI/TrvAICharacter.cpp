// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvAICharacter.h"

#include "BrainComponent.h"
#include "TrvAttributeComponent.h"
#include "TRVWorldUserWidget.h"
#include "AI/TrvAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"


// Sets default values
ATrvAICharacter::ATrvAICharacter()
{
	SensComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensComp"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AttributeComponent = CreateDefaultSubobject<UTrvAttributeComponent>("Attribute Component");
	TimeToHitParamName = "TimeToHit";
}

void ATrvAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SensComp->OnSeePawn.AddDynamic(this, &ATrvAICharacter::OnPawnSeen);
	AttributeComponent->OnHealthChange.AddDynamic(this, &ATrvAICharacter::OnHealthChange);
}

void ATrvAICharacter::SetTargetActor(AActor* TargetActor)
{
	ATrvAIController* AIC = Cast<ATrvAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);
	}
}

void ATrvAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
}

void ATrvAICharacter::OnHealthChange(AActor* Intistigator, UTrvAttributeComponent* OwningComp, float NewHealth,
                                     float Delta)
{
	if (Delta < 0.0f)
	{
		if (Intistigator != this)
		{
			SetTargetActor(Intistigator);
		}
		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UTRVWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		if (NewHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			SetLifeSpan(10.0f);
		}
	}
}
