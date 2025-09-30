// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppPrintfExtraArg
#include "TrvBarrel.h"

// Sets default values
ATrvBarrel::ATrvBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh_Component");
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->ImpulseStrength = 2500.0f;
	RadialForceComponent->Radius = 750.0f;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrvBarrel::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ATrvBarrel::OnActorHit);
}

void ATrvBarrel::OnActorHit(UPrimitiveComponent* HitComponent,
                            AActor* OtherActor,
                            UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse,
                            const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();


	UE_LOG(LogTemp, Log, TEXT("RadialForceComponent"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor %s, at time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString;
	CombinedString = FString::Printf(TEXT("hit at %s"), *Hit.ImpactPoint.ToString());

	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
void ATrvBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
