
#include "Controller/MenuController.h"

#include "Blueprint/UserWidget.h"

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(StartGameHUDWidgetClass))
	{
		StartGameHUDWidgetInstance = CreateWidget<UUserWidget>(this, StartGameHUDWidgetClass);
		if (IsValid(StartGameHUDWidgetInstance))
		{
			StartGameHUDWidgetInstance->AddToViewport();
		}
	}
}
