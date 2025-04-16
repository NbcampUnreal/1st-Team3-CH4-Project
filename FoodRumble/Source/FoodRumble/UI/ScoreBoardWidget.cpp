#include "UI/ScoreBoardWidget.h"

#include "GameState/NewGS.h"
#include "Character/NewPlayerState.h"
#include "UI/ScoreWidget.h"

#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void UScoreBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

    UpdateScoreBoard();
	//GetWorld()->GetTimerManager().SetTimer(ScoreUpdateTimer, this, &ThisClass::UpdateScoreBoard, 0.1f, true);
}

void UScoreBoardWidget::UpdateScoreBoard()
{
    //need to stop game! -> runtime error (this widget class already destroyed)
	if (!IsValid(ScoreWidgetClass))
	{
		return;
	}
    if (!IsValid(ScoreWidgetList))
    {
        return;
    }

	ScoreWidgetList->ClearChildren();

    AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
    if (!IsValid(GameState))
    {
        return;
    }

    TArray<APlayerState*> APS = GameState->PlayerArray;
    APS.Sort([](APlayerState& A, APlayerState& B)
        {
            return Cast<ANewPlayerState>(&A)->GetPlayerIndex() < Cast<ANewPlayerState>(&B)->GetPlayerIndex();
        });

    for (APlayerState* PS : APS)
    {
        ANewPlayerState* NewPS = Cast<ANewPlayerState>(PS);
        if (!IsValid(NewPS))
        {
            continue;        
        }

        UScoreWidget* ScoreWidget = CreateWidget<UScoreWidget>(this, ScoreWidgetClass);
        if (IsValid(ScoreWidget))
        {
            ScoreWidget->SetUIPlayerName(NewPS->GetPlayerIndex());
            ScoreWidget->SetUIPlayerScore(NewPS->GetPlayerScore());
            ScoreWidgetList->AddChildToVerticalBox(ScoreWidget);
        }
    }
}