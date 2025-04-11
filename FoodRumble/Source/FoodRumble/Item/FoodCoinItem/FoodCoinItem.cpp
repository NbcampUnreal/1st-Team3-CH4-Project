#include "Item/FoodCoinItem/FoodCoinItem.h"
#include "Item/FoodCoinItem/PlayerCoinComponent.h"
#include "Item/ItemSpawnRow.h"

AFoodCoinItem::AFoodCoinItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFoodCoinItem::ActivateItem_Implementation(AActor* TargetActor)
{
	if (ItemDataTable && ItemRowName != NAME_None)
	{
		
		const FItemSpawnRow* Row = ItemDataTable->FindRow<FItemSpawnRow>(ItemRowName, TEXT("Finding CoinItem"));
		if (Row)
		{
			UPlayerCoinComponent* CoinComponent = TargetActor->FindComponentByClass<UPlayerCoinComponent>();
			if (CoinComponent)
			{
				CoinComponent->AddCoins(FMath::TruncToInt(Row->ItemScore));
			}
			
		}
	}
}
