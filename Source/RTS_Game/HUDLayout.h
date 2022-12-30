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

	
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;

};
