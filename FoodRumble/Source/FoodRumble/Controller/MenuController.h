

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

UCLASS()
class FOODRUMBLE_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>StartGameHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget>StartGameHUDWidgetInstance;
};
