// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingPlacement.h"
#include "DragWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"

void UBuildingPlacement::NativeConstruct()
{
	Super::NativeConstruct();

	try
	{
		//Getting the Image of the Cube used in the UI
		//Using Try/Catch because It sometimes gave a null reference
		theImage = Cast<UImage>(GetWidgetFromName(TEXT("CubeImage")));
	}
	catch (const std::exception &e)
	{
		UE_LOG(LogTemp, Error, TEXT("Mouse Button Down"), *e.what());
	}
}

FReply UBuildingPlacement::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mouse Button Down"));
	if (theImage != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Setting Color"));
		//Highlighting the color of the building to red upon mouse down
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


// Drag Operation
void UBuildingPlacement::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Detected"));

	UDragWidget *DragDropOperation = NewObject<class UDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
}

// Drag Over
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
