// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCube.h"

// Sets default values
ASpawnCube::ASpawnCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    SphereMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawnCube::BeginPlay()
{
	Super::BeginPlay();
	
	// const FVector Location = GetActorLocation();
	// const FRotator Rotation = GetActorRotation();
	// GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
}


