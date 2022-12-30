// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnCube.generated.h"

UCLASS()
class RTS_GAME_API ASpawnCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnCube();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    UStaticMeshComponent* SphereMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

};
