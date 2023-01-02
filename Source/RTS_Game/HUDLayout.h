// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"
#include "HUDLayout.generated.h"
/**
 * 
 */
UCLASS()
class RTS_GAME_API UHUDLayout : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply CustomDetectMouseClick(const FPointerEvent& InMouseEvent, FKey DragKey);

protected:
	//Calling NativeOnDrop on another class because if we called it on BuildingPlacement we won't be able to get the value since it's a bool.
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

};
