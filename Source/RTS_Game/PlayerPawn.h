// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// Creating the classes used in the .h file
class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

UCLASS()
class RTS_GAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

	//Editor Modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxZoom = 3000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinZoom = -3000.0f;

private:
	UPROPERTY()
	FVector WorldPos;

	UPROPERTY()
	FVector2D MousePos;

	UPROPERTY()
	USceneComponent *RootScene;

	UPROPERTY()
	USpringArmComponent *SpringArmComp;

	UPROPERTY()
	FVector Start;
	
	UPROPERTY()
	FVector End;

	UPROPERTY()
	FHitResult Hit;

	UPROPERTY()
	UCameraComponent *CameraComp;

	float AngleAxis;
	bool executeOnce = false;
	FVector theHitLocation;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Multiplier;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector Dimensions;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void RotateCamera(float AxisValue);
	void ZoomCamera(float AxisValue);
	void OnMouseWheelClicked(float WheelDelta);
	void MouseToWorldPosition();
};
