// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPlacement.generated.h"
/**
 * 
 */

 //The pieces of UI that we want to be draggable.

UCLASS()
class UBuildingPlacement : public UUserWidget
{
	GENERATED_BODY()

public:

	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelected, bool);
	// FOnBuildingSelected BuildingSelectionDelegate;
	bool BuildingSelected = false;

protected:


	//This step enables us to determine if the player is dragging the Left Mouse Button.
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	//virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	//virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual FReply NativeOnMouseButtonUp( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

	FReply CustomDetectDrag( const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey );

	//bool BuildingSelected = false;

	virtual void NativeConstruct() override;

	void DragBuilding();
};
