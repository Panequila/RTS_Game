// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPlacement.generated.h"

UCLASS()
class UBuildingPlacement : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	class UImage* theImage;

	UPROPERTY()
	class UEditableText* theName;
	//Tried to make an event.. needed more time to make it work so instead I added the variable to the PlayerController so that it becomes accessible for now.
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelected, bool);
	// FOnBuildingSelected BuildingSelectionDelegate;

	//bool BuildingSelected = false;

protected:

	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	//virtual void NativeOnDragLeave( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	//virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

	FReply CustomDetectDrag( const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey );

	virtual void NativeConstruct() override;

};
