// Fill out your copyright notice in the Description page of Project Settings.


#include "TrvCharacter.h"
#include "GameFramework/Character.h"
#include "TrvAttributeComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TrvInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATrvCharacter::ATrvCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UTrvInteractionComponent>("Interaction Component");

	AttributeComponent = CreateDefaultSubobject<UTrvAttributeComponent>("Attribute Component");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ATrvCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ATrvCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &ATrvCharacter::OnHealthChange);
}

void ATrvCharacter::Move(const FInputActionValue& Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.0f;
	ControlRot.Pitch = 0.0f;

	FVector2d InputValue = Value.Get<FVector2D>();
	AddMovementInput(ControlRot.Vector(), InputValue.Y);

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, InputValue.X);
}

void ATrvCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
}

void ATrvCharacter::PrimaryA()
{
	PlayAnimMontage(AttackAnim);
	FTimerDelegate Del;
	Del.BindUFunction(this, FName("AttackElapsed"), ProjectileClass);
	GetWorldTimerManager().SetTimer(TimerHandle_Pa, Del, 0.2f, false);
}

void ATrvCharacter::SecondaryA()
{
	PlayAnimMontage(AttackAnim);
	FTimerDelegate Del;
	Del.BindUFunction(this, FName("AttackElapsed"), ProjectileClassA);
	GetWorldTimerManager().SetTimer(TimerHandle_Pa, Del, 0.2f, false);
}

void ATrvCharacter::DashA()
{
	PlayAnimMontage(AttackAnim);
	FTimerDelegate Del;
	Del.BindUFunction(this, FName("AttackElapsed"), DashProjectile);
	GetWorldTimerManager().SetTimer(TimerHandle_Pa, Del, 0.2f, false);
}

void ATrvCharacter::AttackElapsed(const TSubclassOf<AActor> Ammo)
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	const FVector EyeLocation = CameraComp->GetComponentLocation();
	const FRotator EyeRotation = CameraComp->GetComponentRotation();

	const FVector End = EyeLocation + (EyeRotation.Vector() * 100000);

	FVector Target;

	if (FHitResult Hit; GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams))
	{
		Target = Hit.Location;
	}
	else
	{
		Target = Hit.TraceEnd;
	}

	const FRotator Rot = UKismetMathLibrary::FindLookAtRotation(HandLocation, Target);
	const FTransform SpawnTM = FTransform(Rot, HandLocation);
	GetWorld()->SpawnActor<AActor>(Ammo, SpawnTM, SpawnParams);
}

void ATrvCharacter::OnHealthChange(AActor* Intistigator, UTrvAttributeComponent* OwningComp, float NewHealth,
                                   float Delta)
{
	if (NewHealth <= 0.0f && Delta <= 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ATrvCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteraction();
}

// Called every frame
void ATrvCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrvCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATrvCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATrvCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATrvCharacter::Jump);
		EnhancedInputComponent->BindAction(PrimaryAttack, ETriggerEvent::Triggered, this, &ATrvCharacter::PrimaryA);
		EnhancedInputComponent->BindAction(SecondaryAttack, ETriggerEvent::Triggered, this, &ATrvCharacter::SecondaryA);
		EnhancedInputComponent->BindAction(DashAttack, ETriggerEvent::Triggered, this, &ATrvCharacter::DashA);
		EnhancedInputComponent->BindAction(Interact, ETriggerEvent::Triggered, this, &ATrvCharacter::PrimaryInteract);
	}
}
