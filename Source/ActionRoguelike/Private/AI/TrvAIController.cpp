// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void ATrvAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("BehaviorTree is NUll! Assign behavior tree")))
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	RunBehaviorTree(BehaviorTree);
	
}
