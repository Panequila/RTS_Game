// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating the camera here in the class didn't make the rotation work properly, the bug was that the camera was the object that rotated not the spring arm.
	//I had to create the camera and the spring arm in the blueprint in order for it work right.

	#pragma region Camera Creation Code
	// RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	// RootComponent = RootScene;

	// SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	// SpringArmComp->SetupAttachment(RootScene);
	// SpringArmComp->bDoCollisionTest = false;
	// //Setting the starting rotation.
	// //SpringArmComp->SetRelativeRotation(FRotator(-50,0,0));

	// //SpringArmComp->bUsePawnControlRotation = true;
	// SpringArmComp->bEnableCameraLag = true;
	// SpringArmComp->TargetArmLength = 300.0f;


	// CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);

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

	// PlayerInputComponent->BindAxis(TEXT("MouseYaw"), this, &APlayerPawn::MouseYaw);
	// PlayerInputComponent->BindAxis(TEXT("MousePitch"), this, &APlayerPawn::MousePitch);



}

void APlayerPawn::MoveForward(float AxisValue)
{
	//getting the forward value of the pawn
	UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), AxisValue);
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

