// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLayout.h"
#include "DragWidget.h"
#include "PlayerPawn.h"

#include "MyPlayerController.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

bool UHUDLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	AMyPlayerController* PlayerController = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->BuildingSelected = false;
	}


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Drop"));

	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);

	if (!IsValid(DragWidgetResult))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cast Returned Null"));
		return false;

	}

	const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidgetResult->DragOffset;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("My Location is: %s"), *DragWindowOffset.ToString()));


	DragWidgetResult->WidgetReference->AddToViewport();
	DragWidgetResult->WidgetReference->SetVisibility(ESlateVisibility::Visible);
	DragWidgetResult->WidgetReference->SetPositionInViewport(DragWindowOffsetResult, false);


	return true;
}

//Tried to do "Close UI On Right Click"


FReply UHUDLayout::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("On Mouse Button Down"));


	return CustomDetectMouseClick(InMouseEvent, EKeys::RightMouseButton);
	//return FReply();
}

FReply UHUDLayout::CustomDetectMouseClick(const FPointerEvent& InMouseEvent, FKey DragKey)
{
		
	if (InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right Click Outside Widget"));

		// Get a pointer to the player controller
		AMyPlayerController* PC = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
		PC->SetInputMode(FInputModeUIOnly());

		// Get the mouse position
		FVector2D MousePosition;
		PC->GetMousePosition(MousePosition.X, MousePosition.Y);

		// Get the hit result under the mouse cursor
		FHitResult HitResult;
		PC->GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);



		if (HitResult.GetActor() == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Valid"));
		}

		 //Check if the hit result was a widget
		if (HitResult.GetActor() != nullptr) {

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Valid"));

			if (HitResult.GetActor()->IsA<UWidget>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Right Click Inside Widget"));
				// The hit result was a widget
				// You can now cast the hit result to a widget and interact with it
				UWidget* Widget = Cast<UWidget>(HitResult.GetActor());
			}
		}
		

	}
	return FReply::Unhandled();

}





