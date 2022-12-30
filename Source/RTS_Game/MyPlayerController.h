// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//This isn't good practice, it is better to use events and let other classes subscribe to it.
	bool BuildingSelected = false; 
};
