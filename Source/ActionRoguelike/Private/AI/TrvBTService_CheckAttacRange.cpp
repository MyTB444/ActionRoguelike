// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvBTService_CheckAttacRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UTrvBTService_CheckAttacRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent)
	{
		AActor* MyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (MyActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (MyController)
			{
				APawn* AIPawn = MyController->GetPawn();
				if (AIPawn)
				{
					float Distance = FVector::Distance(MyActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool WithinRange = Distance < 2000.f;
					bool hasLos = false;
					if (WithinRange)
					{
						hasLos = MyController->LineOfSightTo(MyActor);
					}
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, (WithinRange && hasLos));
				}
			}
		}
	}
}
