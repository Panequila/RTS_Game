// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingPlacement.h"
#include "DragWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"

void UBuildingPlacement::NativeConstruct()
{
	Super::NativeConstruct();
	theName = Cast<UEditableText>(GetWidgetFromName(TEXT("BuildingName")));
	theImage = Cast<UImage>(GetWidgetFromName(TEXT("CubeImage")));
}

FReply UBuildingPlacement::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	// if (theName != nullptr)
	// {
	// 	theName = Cast<UEditableText>(GetWidgetFromName(TEXT("BuildingName")));
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Casting Done"));
	// }
	// if (theImage != nullptr)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Casting Done"));

	// 	theImage = Cast<UImage>(GetWidgetFromName(TEXT("CubeImage")));
	// }
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NULLLLLLLLL"));
	// }
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mouse Button Down"));
	if (theImage != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setting Color"));
		theImage->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	}

	AMyPlayerController *PlayerController = (AMyPlayerController *)GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->BuildingSelected = true;
	}

	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
	// return FReply();
}

void UBuildingPlacement::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Detected"));

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragWidget *DragDropOperation = NewObject<class UDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
}

void UBuildingPlacement::NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Cancelled"));

	// Setting the buildingSelected bool to false to cancel selection
	AMyPlayerController *PlayerController = (AMyPlayerController *)GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->BuildingSelected = false;
	}
}

bool UBuildingPlacement::NativeOnDragOver(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDragDetected(InGeometry, InDragDropEvent, InOperation);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Over"));

	// Setting the buildingSelected bool to true
	AMyPlayerController *PlayerController = (AMyPlayerController *)GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->BuildingSelected = true;
	}
	return false;
}

// Performing ceratin checking for when the Mouse Button is pressed and what happens when a widget drag is detected.
FReply UBuildingPlacement::CustomDetectDrag(const FPointerEvent &InMouseEvent, UWidget *WidgetDetectingDrag, FKey DragKey)
{
	if (InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/)
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();

		if (WidgetDetectingDrag)
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if (SlateWidgetDetectingDrag.IsValid())
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}
	return FReply::Unhandled();
}
