// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDLayout.h"
#include "DragWidget.h"
#include "PlayerPawn.h"

#include "MyPlayerController.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"


bool UHUDLayout::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    // UWorld* TestWorld = GetWorld();
	// if (TestWorld)
	// {
	// 	AMyPlayerController* PlayerController = (AMyPlayerController*)TestWorld->GetFirstPlayerController();
	// 	FVector2D MousePos = FVector2D(0, 0);
	// 	FVector WorldPos = FVector(MousePos.X, MousePos.Y, 0);
	// 	FVector Dir = FVector(0, 0, 0);
	// 	if (PlayerController != nullptr)
	// 	{
	// 		PlayerController->GetMousePosition(MousePos.X, MousePos.Y);
	// 		PlayerController->DeprojectMousePositionToWorld(WorldPos, Dir);
	// 	}
	// 	const FVector2D mousePosition = FVector2D((int)(WorldPos.X/1), (int)(WorldPos.Y/1));
    //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mouse Position to World is: %s"), *WorldPos.ToString()));

	// 	FVector Start = WorldPos;
	// 	FVector End = WorldPos + (Dir * 1000);
	// 	FHitResult Hit;
	// 	FCollisionQueryParams TraceParams;
	// 	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	// 	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);
	// }

    //UDragWidget* DragDropOperation = NewObject<class UDragWidget>();
	//APlayerPawn* PP = NewObject<class APlayerPawn>();
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mouse Position to World is: %s"), *PP->WorldPos.ToString()));
 

    AMyPlayerController* PlayerController = (AMyPlayerController*)GetWorld()->GetFirstPlayerController();
	if(PlayerController!=nullptr){
		PlayerController->BuildingSelected = false;
	}
    

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Drag Drop"));

	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);

    if(!IsValid(DragWidgetResult))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cast Returned Null"));
        return false;

    }
    
	const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidgetResult->DragOffset;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("My Location is: %s"), *DragWindowOffset.ToString()));


    DragWidgetResult->WidgetReference->AddToViewport();
    DragWidgetResult->WidgetReference->SetVisibility(ESlateVisibility::Visible);
    DragWidgetResult->WidgetReference->SetPositionInViewport(DragWindowOffsetResult, false);


    return true;
}

