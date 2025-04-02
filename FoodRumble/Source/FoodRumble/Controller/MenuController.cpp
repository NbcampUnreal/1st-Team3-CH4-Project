
#include "Controller/MenuController.h"

#include "Blueprint/UserWidget.h"

AMenuController::AMenuController()
{

}

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	
	bShowMouseCursor = true;

	if (StartGameHUDWidgetInstance)
	{
		StartGameHUDWidgetInstance->RemoveFromParent();
		StartGameHUDWidgetInstance = nullptr;
	}

	if (IsValid(StartGameHUDWidgetClass))
	{
		StartGameHUDWidgetInstance = CreateWidget<UUserWidget>(this, StartGameHUDWidgetClass);
		if (IsValid(StartGameHUDWidgetInstance))
		{
			StartGameHUDWidgetInstance->AddToViewport();
		}
	}
}
