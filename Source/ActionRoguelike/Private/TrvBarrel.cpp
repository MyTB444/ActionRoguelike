// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvBarrel.h"

#include "Components/CapsuleComponent.h"

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
	DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 50.f, 16, FColor::Green, false, 1.5f);
}
// Called every frame
void ATrvBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

