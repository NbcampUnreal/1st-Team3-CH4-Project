#include "Item/FoodCoinItem/PlayerCoinComponent.h"


UPlayerCoinComponent::UPlayerCoinComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentCoins = 0;
}

void UPlayerCoinComponent::AddCoins(int32 Amount)
{
	CurrentCoins += Amount;
}


void UPlayerCoinComponent::RemoveCoins(int32 Amount)
{
	CurrentCoins = FMath::Max(0, CurrentCoins - Amount);
}

int32 UPlayerCoinComponent::GetCurrentCoins() const
{
	return CurrentCoins;
}
