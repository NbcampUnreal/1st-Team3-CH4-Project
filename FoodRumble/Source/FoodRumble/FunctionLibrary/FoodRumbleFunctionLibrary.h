

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "FoodRumbleFunctionLibrary.generated.h"

UCLASS()
class FOODRUMBLE_API UFoodRumbleFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void CreateAndRemoveHUD(UUserWidget* Remove, TSubclassOf<UUserWidget>Widget, APlayerController* Controller)
	{		
		UUserWidget* ResultWidgetInstance = CreateWidget<UUserWidget>(Controller, Widget);
		if (IsValid(ResultWidgetInstance))
		{
			ResultWidgetInstance->AddToViewport();
			Remove->RemoveFromParent();
		}
	}

};
