// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API UDragWidget : public UDragDropOperation
{
	GENERATED_BODY()
	
public:

	//This will be used to hold the UMG Widget that we want to drag around on screen (building)
	//it inherits the DragDropOperation Class for this purpose.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;

};
