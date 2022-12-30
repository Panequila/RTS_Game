// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacement.h"
#include "DragWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"

FReply UBuildingPlacement::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry,InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mouse Button Down"));

	AMyPlayerController* PlayerController = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
	if(PlayerController!=nullptr){
		PlayerController->BuildingSelected = true;
	}

	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
    //return FReply();
}

void UBuildingPlacement::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Detected"));

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragWidget* DragDropOperation = NewObject<class UDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->WidgetReference = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;

}

void UBuildingPlacement::NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent,InOperation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Cancelled"));

	AMyPlayerController* PlayerController = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
	if(PlayerController!=nullptr){
		PlayerController->BuildingSelected = false;
	}
}

bool UBuildingPlacement::NativeOnDragOver(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
		Super::NativeOnDragDetected(InGeometry, InDragDropEvent, InOperation);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Over"));

	AMyPlayerController* PlayerController = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
	if(PlayerController!=nullptr){
		PlayerController->BuildingSelected = true;
	}
    return false;
}

FReply UBuildingPlacement::CustomDetectDrag(const FPointerEvent &InMouseEvent, UWidget *WidgetDetectingDrag, FKey DragKey)
{
    if ( InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/ )
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();
		
		if ( WidgetDetectingDrag )
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if ( SlateWidgetDetectingDrag.IsValid() )
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}
	return FReply::Unhandled();
}

void UBuildingPlacement::NativeConstruct()
{
	Super::NativeConstruct();

}

