// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "TRVWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UTRVWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;
	
	virtual void NativeTick(const FGeometry& Geometry, float dt) override;
	
public:
	
	UPROPERTY(EditAnywhere, Category= "UI")
	FVector WorldOffset;
	
	UPROPERTY(BlueprintReadOnly, Category= "UI")
	AActor* AttachedActor;
};
