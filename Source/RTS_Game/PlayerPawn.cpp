// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "BuildingPlacement.h"
#include "SpawnCube.h"
// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//BluePrint_PlayerPawn is the default pawn which inherits this PlayerPawn class.
	//Inorder to use the PlayerPawn as the default pawn, I need to use the "FloatingPawnMovement" in here as it is responosible for the movement.
	

	#pragma region Camera & SpringArm Creation

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootScene);
	SpringArmComp->bDoCollisionTest = false;
	//Setting the starting rotation.
	SpringArmComp->SetRelativeRotation(FRotator(-50,0,0));

	//SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->TargetArmLength = 300.0f;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

	#pragma endregion
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* TestWorld = GetWorld();
	AMyPlayerController* PlayerController = (AMyPlayerController*)TestWorld->GetFirstPlayerController();
	if(!PlayerController->BuildingSelected){
	if (TestWorld)
	{
		FVector2D MousePos = FVector2D(0, 0);
		WorldPos = FVector(MousePos.X, MousePos.Y, 0);
		FVector Dir = FVector(0, 0, 0);
		if (PlayerController != nullptr)
		{
			PlayerController->GetMousePosition(MousePos.X, MousePos.Y);
			PlayerController->DeprojectMousePositionToWorld(WorldPos, Dir);
		}
		const FVector2D mousePosition = FVector2D((int)(WorldPos.X/1), (int)(WorldPos.Y/1));
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mouse Position to World is: %s"), *WorldPos.ToString()));


		
		//if(buildingPlacement->BuildingSelected)

		FVector Start = WorldPos;
		FVector End = WorldPos + (Dir * 10000000);
		FHitResult Hit;
		FCollisionQueryParams TraceParams;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
		DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);

		
			if(GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams))
			{

				FActorSpawnParameters SpawnInfo;
				GetWorld()->SpawnActor<ASpawnCube>(ActorToSpawn, Hit.Location, FRotator(0,0,0), SpawnInfo);
				PlayerController->BuildingSelected = true;

			}
		}
	}
	//Controller->GetControlRotation();
	// FRotator newYaw = GetActorRotation();
	// FRotator newPitch = SpringArmComp->GetComponentRotation();
	// newYaw.Yaw += mouseInput.X;
	// newPitch.Pitch += mouseInput.Y;
	// SetActorRotation(newYaw);
	// SpringArmComp->SetWorldRotation(newPitch);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateCamera"), this, &APlayerPawn::RotateCamera);
	PlayerInputComponent->BindAxis(TEXT("ZoomCamera"), this, &APlayerPawn::ZoomCamera);

	// PlayerInputComponent->BindAxis(TEXT("MouseYaw"), this, &APlayerPawn::MouseYaw);
	// PlayerInputComponent->BindAxis(TEXT("MousePitch"), this, &APlayerPawn::MousePitch);



}

void APlayerPawn::MoveForward(float AxisValue)
{
	//getting the forward value of the pawn
	//UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), AxisValue);
	//MovementDirection.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerPawn::MoveRight(float AxisValue)
{
	//getting the right value of the pawn
	//MovementDirection.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerPawn::RotateCamera(float AxisValue)
{

	//AddActorLocalRotation(FRotator(0, AxisValue, 0));
	//SetActorRotation(GetActorRotation(),FRotator(0,AxisValue,0));
	//AddMovementInput(GetActorRotationVector(),AxisValue*500);

	//Changing the Yaw value according the rotation input.
	FRotator NewRotation = FRotator(0.f,AxisValue,0.f);
	//Turning the Euler rotation to Quternion.
	FQuat QuatRotation = FQuat(NewRotation);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
	
}

void APlayerPawn::ZoomCamera(float AxisValue)
{
	//increasing or decreasing the arm length by the rotation speed
	SpringArmComp->TargetArmLength += AxisValue * 100.f;
}
