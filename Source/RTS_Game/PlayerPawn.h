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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	FVector WorldPos;

	UPROPERTY()
	USceneComponent* RootScene;

	UPROPERTY()
	USpringArmComponent* SpringArmComp;

	UPROPERTY()
	UCameraComponent* CameraComp;

	UPROPERTY()
	UFloatingPawnMovement* FPM;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

private:
	FVector MovementDirection;
	FVector RotationDirection;


	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void RotateCamera(float AxisValue); 
	void ZoomCamera(float AxisValue);

	// void MouseYaw(float axis);
	// void MousePitch(float axis);
	// FVector2D mouseInput;

};
