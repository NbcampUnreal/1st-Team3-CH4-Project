#include "UI/PlayerNumberText.h"

#include "Character/NewCharacter.h"
#include "Character/NewPlayerState.h"

#include "Components/TextBlock.h"

UPlayerNumberText::UPlayerNumberText(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerNumberText::NativeConstruct()
{
	Super::NativeConstruct();

	SetPlayerNumber(1);
}

void UPlayerNumberText::SetPlayerNumber(int32 InIndex)
{	
	FString OutString = FString::Printf(TEXT("Player #%d"), InIndex);
	PlayerNumberText->SetText(FText::FromString(OutString));
}
