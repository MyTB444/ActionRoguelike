// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvGameModeBase.h"

#include "EngineUtils.h"
#include "TrvAttributeComponent.h"
#include "TrvCharacter.h"
#include "AI/TrvAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include  "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Net/Core/Analytics/NetStatsUtils.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Bot spawn enabled"), ECVF_Cheat);

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

void ATrvGameModeBase::KillALl()
{
	for (TActorIterator<ATrvAICharacter> IT(GetWorld()); IT; ++IT)
	{
		ATrvAICharacter* Bot = *IT;
		UTrvAttributeComponent* AttComp = UTrvAttributeComponent::GetAttributes(Bot);
		if (AttComp && AttComp->IsAlive())
		{
			AttComp->Kill(this);
		}
	}
}


void ATrvGameModeBase::SpawnTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
		return;
	int NrOfAliveBots = 0;
	for (TActorIterator<ATrvAICharacter> IT(GetWorld()); IT; ++IT)
	{
		ATrvAICharacter* Bot = *IT;
		UTrvAttributeComponent* AttComp = UTrvAttributeComponent::GetAttributes(Bot);
		if (AttComp && AttComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}
	float MaxBot = 10.0f;
	if (DifficultyCurve)
	{
		MaxBot = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	if (NrOfAliveBots > MaxBot)
	{
		return;
	}
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
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}
void ATrvGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}
void ATrvGameModeBase::OnActorKilled(AActor* Actor, AActor* Killer)
{
	ATrvCharacter* Player = Cast<ATrvCharacter>(Actor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, TimerDelegate,	2.0f, false);
	}
}

