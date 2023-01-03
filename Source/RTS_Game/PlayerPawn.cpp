// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "MyPlayerController.h"
#include "BuildingPlacement.h"
#include "SpawnCube.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BluePrint_PlayerPawn is the default pawn which inherits this PlayerPawn class.
	// Inorder to use the PlayerPawn as the default pawn, I need to use the "FloatingPawnMovement" in here as it is responosible for the movement.

#pragma region Camera &SpringArm Creation

	// Creating a Camera and attaching it to the SpringArm
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootScene);
	SpringArmComp->bDoCollisionTest = false;
	// Setting the starting rotation.
	SpringArmComp->SetRelativeRotation(FRotator(5000, 0, 0));

	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 150.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

#pragma endregion
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	AngleAxis = 0.f;
	// distance between the player and the point
	Dimensions = FVector(300, 0, 0);
	// which access we want to rotate around
	AxisVector = FVector(0, 0, 1);
	Multiplier = 50.f;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld *theWorld = GetWorld();
	AMyPlayerController *PlayerController = (AMyPlayerController *)theWorld->GetFirstPlayerController();

	if (!PlayerController->BuildingSelected)
	{
		// If there is a world/level created.
		if (theWorld)
		{
			MouseToWorldPosition();
			FCollisionQueryParams TraceParams;

			if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams))
			{
				FActorSpawnParameters SpawnInfo;
				// Spawn the building at the hit location
				GetWorld()->SpawnActor<ASpawnCube>(ActorToSpawn, Hit.Location, FRotator(0, 0, 0), SpawnInfo);
				// Set the bool to true so that it stops spawning after DragDrop
				PlayerController->BuildingSelected = true;
			}
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &APlayerPawn::RotateCamera);
	PlayerInputComponent->BindAxis(TEXT("ZoomCamera"), this, &APlayerPawn::ZoomCamera);
	PlayerInputComponent->BindAxis(TEXT("OnMouseWheelClicked"), this, &APlayerPawn::OnMouseWheelClicked);
}

void APlayerPawn::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerPawn::MoveRight(float AxisValue)
{

	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerPawn::RotateCamera(float AxisValue)
{

	// Changing the Yaw value according the rotation input.
	FRotator NewRotation = FRotator(0.f, AxisValue, 0.f);
	// Turning the Euler rotation to Quternion.
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void APlayerPawn::ZoomCamera(float AxisValue)
{
	// Clamping the ArmLength by the modifier values.
	SpringArmComp->TargetArmLength = FMath::Clamp(SpringArmComp->TargetArmLength += AxisValue * 100.f, MinZoom, MaxZoom);
}

void APlayerPawn::OnMouseWheelClicked(float WheelDelta)
{
	// If the mouse wheel isn't clicked -> We get the Hit Location
	if (WheelDelta == 0)
	{
		executeOnce = true;
	}
	if (WheelDelta != 0)
	{
		if (executeOnce == true)
		{
			MouseToWorldPosition();
			theHitLocation = Hit.Location;
			theHitLocation.Z = 500.f;
			// Setting this bool to false so that we don't get keep getting new values for the Hit Location .. we only want the one where the mouse clicked
			executeOnce = false;
		}
		AngleAxis += WheelDelta * 0.5f;

		FRotator NewRotation = FRotator(0, AngleAxis, 0);
		FQuat QuatRotation = FQuat(NewRotation);

		SetActorLocationAndRotation(theHitLocation, QuatRotation, false, 0, ETeleportType::None);
	}
}

void APlayerPawn::MouseToWorldPosition()
{
	// The World is the top level object representing the map in which Actors and Components will exist and be rendered.
	UWorld *TheWorld = GetWorld();
	// From the world we get the player controller
	AMyPlayerController *PlayerController = (AMyPlayerController *)TheWorld->GetFirstPlayerController();
	MousePos = FVector2D(0, 0);
	WorldPos = FVector(MousePos.X, MousePos.Y, 0);
	FVector Dir = FVector(0, 0, 0);
	if (PlayerController != nullptr)
	{
		PlayerController->GetMousePosition(MousePos.X, MousePos.Y);
		PlayerController->DeprojectMousePositionToWorld(WorldPos, Dir);
	}
	Start = WorldPos;
	End = WorldPos + (Dir * 10000000);
	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(TheWorld, Start, End, FColor::Red, false, 2.0f);
}
