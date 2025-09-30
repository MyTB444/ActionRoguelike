// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void ATrvAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* mypawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (mypawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", mypawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", mypawn);
	}
}
