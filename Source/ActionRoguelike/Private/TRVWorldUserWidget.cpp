// Fill out your copyright notice in the Description page of Project Settings.


#include "TRVWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTRVWorldUserWidget::NativeTick(const FGeometry& Geometry, float dt)
{
	Super::NativeTick(Geometry, dt);
	
	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;
		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
		
	}
}
