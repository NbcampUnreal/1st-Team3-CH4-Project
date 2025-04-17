#include "UI/StartGameButton.h"

#include "GameMode/NewGM.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UStartGameButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(StartGameButton))
	{
		StartGameButton->SetVisibility(ESlateVisibility::Hidden);

		OwningActor = GetOwningPlayer();
		if (IsValid(OwningActor) && OwningActor->HasAuthority())
		{
			StartGameButton->SetVisibility(ESlateVisibility::Visible);
			StartGameButton->SetIsEnabled(false);
			StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
		}
	}
}

void UStartGameButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsValid(OwningActor) && OwningActor->HasAuthority())
	{
		AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld());

		if (IsValid(GM))
		{
			ANewGM* NewGM = Cast<ANewGM>(GM);
			if (IsValid(NewGM))
			{
				if (NewGM->GetIsReady())
				{
					StartGameButton->SetIsEnabled(true);
				}
			}
		}
	}
}

void UStartGameButton::OnButtonClicked()
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(GetWorld());
	if (IsValid(GM))
	{
		ANewGM* NewGM = Cast<ANewGM>(GM);
		if (IsValid(NewGM))
		{
			RemoveFromParent();
			NewGM->CanStartGame();
		}
	}	
}
