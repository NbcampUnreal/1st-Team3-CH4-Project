

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoardWidget.generated.h"

class UVerticalBox;
class UScoreWidget;
class UTextBlock;

UCLASS()
class FOODRUMBLE_API UScoreBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateScoreBoard();

	void ClearTimer() { GetWorld()->GetTimerManager().ClearTimer(ScoreUpdateTimer); }
	/*UFUNCTION()
	void UpdateTimer();*/

protected:
	FTimerHandle ScoreUpdateTimer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ScoreWidgetList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UTextBlock> MainLoopTimerText;

};
