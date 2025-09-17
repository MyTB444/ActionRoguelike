// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvMagicProjectile.h"

#include "TrvAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
ATrvMagicProjectile::ATrvMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrvMagicProjectile::OnActorOverlap);
	RootComponent = SphereComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ATrvMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrvMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATrvMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UTrvAttributeComponent* AttributeComponent = Cast<UTrvAttributeComponent>(OtherActor->GetComponentByClass(UTrvAttributeComponent::StaticClass()));
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-20.0f);
			Destroy();
		}
	}
}


