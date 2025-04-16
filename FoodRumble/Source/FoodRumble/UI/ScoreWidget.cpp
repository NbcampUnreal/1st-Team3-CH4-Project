#include "UI/ScoreWidget.h"
#include "Components/TextBlock.h"

//void UScoreWidget::SetUIScore(int32 InScore)
//{
//	if (IsValid(PlayerScore))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%d"), InScore);
//		//UE_LOG(LogTemp, Warning, );
//
//		PlayerScore->SetText(FText::AsNumber(InScore));
//	}
//}

//void UScoreWidget::SetUIText(int32 InScore, int32 InIndex)
//{
//	if (IsValid(PlayerNameAndScore))
//	{
//		FString OutString = FString::Printf(TEXT("Player %d : %d"), InIndex, InScore);
//		PlayerNameAndScore->SetText(FText::FromString(OutString));
//	}
//}

void UScoreWidget::SetUIPlayerName(int32 InIndex)
{
	if (IsValid(PlayerName))
	{
		FString OutString = FString::Printf(TEXT("Player #%d "), InIndex);
		PlayerName->SetText(FText::FromString(OutString));
	}
}

void UScoreWidget::SetUIPlayerScore(int32 InScore)
{
	if (IsValid(PlayerScore))
	{
		PlayerScore->SetText(FText::AsNumber(InScore));
	}
}
