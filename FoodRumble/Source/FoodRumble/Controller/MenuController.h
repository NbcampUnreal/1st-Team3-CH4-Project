

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

UCLASS()
class FOODRUMBLE_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	AMenuController();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>StartGameHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget>StartGameHUDWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>MapSelectHUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget>MapSelectHUDWidgetInstance;
};
