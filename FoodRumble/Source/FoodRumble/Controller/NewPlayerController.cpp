#include "Controller/NewPlayerController.h"

#include "UI/GameEndWidget.h"
#include "UI/ScoreBoardWidget.h"

#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
void ANewPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	if (IsValid(NotificationTextUIClass))
	{
		NotificationTextUIInstance = CreateWidget<UUserWidget>(this, NotificationTextUIClass);
		if (IsValid(NotificationTextUIInstance))
		{
			NotificationTextUIInstance->AddToViewport(1);

			NotificationTextUIInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ANewPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
	DOREPLIFETIME(ThisClass, MainLoopTimerText);
}

void ANewPlayerController::ClientRPCShowScoreWidget_Implementation()
{
	if (NotificationTextUIInstance)
	{
		NotificationTextUIInstance->RemoveFromParent();
		NotificationTextUIInstance = nullptr;
	}

	if (ScoreWidgetInstance)
	{
		ScoreWidgetInstance->RemoveFromParent();
		ScoreWidgetInstance = nullptr;
	}

	if (IsValid(ScoreWidgetClass))
	{
		ScoreWidgetInstance = CreateWidget<UUserWidget>(this, ScoreWidgetClass);
		if (IsValid(ScoreWidgetInstance))
		{
			//Update HUD
			ScoreWidgetInstance->AddToViewport(1);			
			ScoreWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ANewPlayerController::ClientRPCShowEndGameWidget_Implementation(int32 WinnerIndex)
{
	if (NotificationTextUIInstance)
	{
		NotificationTextUIInstance->RemoveFromParent();
		NotificationTextUIInstance = nullptr;
	}

	if (IsValid(EndGameWidgetClass))
	{
		EndGameWidgetInstance = CreateWidget<UUserWidget>(this, EndGameWidgetClass);
		if (IsValid(EndGameWidgetInstance))
		{
			EndGameWidgetInstance->AddToViewport(1);
			EndGameWidgetInstance->SetVisibility(ESlateVisibility::Visible);

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
			SetPause(true);

			UGameEndWidget* GameEndWidget = Cast<UGameEndWidget>(EndGameWidgetInstance);
			if (IsValid(GameEndWidget))
			{
				GameEndWidget->SetEndGameUI(WinnerIndex);
			}
		}
	}

	if (ScoreWidgetInstance)
	{
		Cast<UScoreBoardWidget>(ScoreWidgetInstance)->ClearTimer();
		ScoreWidgetInstance->RemoveFromParent();
		ScoreWidgetInstance = nullptr;
	}
}