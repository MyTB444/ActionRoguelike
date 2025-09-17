// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrvAttributeComponent.h"
#include "TrvInteractionComponent.h"
#include "GameFramework/Character.h"
#include "TrvCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
UCLASS()
class ACTIONROGUELIKE_API ATrvCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATrvCharacter();
protected:
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PrimaryA();
	void PrimaryInteract();
	void PrimaryA_Elapsed();
	
	FTimerHandle TimerHandle_Pa;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	UTrvInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTrvAttributeComponent* AttributeComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;
};
