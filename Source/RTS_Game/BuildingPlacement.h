#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPlacement.generated.h"

// We make the class abstract, as we don't want to create
// instances of this, instead we want to create instances
// of our UMG Blueprint subclass.
UCLASS(Abstract)
class RTS_GAME_API UBuildingPlacement : public UUserWidget
{
	GENERATED_BODY()

    
public:

};