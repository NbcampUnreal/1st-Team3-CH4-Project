

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class FOODRUMBLE_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetEndGameUI(int32 WinnerIndex);

	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void OnReturnToTitleButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WinnerText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> ReturnToTitleButton;
};
