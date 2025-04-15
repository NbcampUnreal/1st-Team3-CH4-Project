#include "UI/GameEndWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameEndWidget::SetEndGameUI(int32 WinnerIndex)
{
	if (IsValid(WinnerText))
	{
		FString OutString = FString::Printf(TEXT("Player #%d Win!"), WinnerIndex);
		WinnerText->SetText(FText::FromString(OutString));
	}
}

void UGameEndWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGameEndWidget::OnReturnToTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MenuMap")), true);
}
