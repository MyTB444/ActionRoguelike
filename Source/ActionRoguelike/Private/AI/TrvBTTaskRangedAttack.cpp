// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TrvBTTaskRangedAttack.h"

#include "AIController.h"
#include "TrvAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UTrvBTTaskRangedAttack::UTrvBTTaskRangedAttack()
{
	MaxBulletSpread = 2.0f;
}

EBTNodeResult::Type UTrvBTTaskRangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		ACharacter* MyChar = Cast<ACharacter>(AIController->GetPawn());
		if (MyChar == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLocation = MyChar->GetMesh()->GetSocketLocation("Muzzle_01");
		AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (Target == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (!UTrvAttributeComponent::IsActorAlive(Target))
		{
			return EBTNodeResult::Failed;
		}
		FVector Direction = Target->GetActorLocation() - MuzzleLocation;
		FRotator Rotation = Direction.Rotation();

		Rotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
		Rotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = MyChar;

		AActor* NewProj = OwnerComp.GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, Rotation,
		                                                           SpawnParameters);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
