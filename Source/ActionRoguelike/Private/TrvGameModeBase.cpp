// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include  "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"


ATrvGameModeBase::ATrvGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ATrvGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ATrvGameModeBase::SpawnTimerElapsed,
	                                SpawnTimerInterval, true);
}


void ATrvGameModeBase::SpawnTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
		this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ATrvGameModeBase::OnQueryCompleted);
	}
}

void ATrvGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                        EEnvQueryStatus::Type QueryStatus)
{
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (ensure(Locations.IsValidIndex(0)))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator, SpawnParams);
	}
}
