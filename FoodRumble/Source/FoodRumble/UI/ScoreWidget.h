

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class FOODRUMBLE_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetUIPlayerName(int32 InIndex);

	UFUNCTION()
	void SetUIPlayerScore(int32 InScore);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerScore;
};
