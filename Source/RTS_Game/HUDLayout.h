// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"
#include "HUDLayout.generated.h"

// DECLARE_DYNAMIC_DELEGATE(FOnBuildingDropped);

UCLASS()
class RTS_GAME_API UHUDLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	// FOnBuildingDropped OnBuildingDropped;

	UPROPERTY()
	class UWidget *CubeWidgetHolder;

protected:
	// Implementing the Drop function here because we can't do it in BuildingPlacement..
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;
	FReply CustomDetectMouseClick(const FPointerEvent &InMouseEvent, FKey DragKey);
};
