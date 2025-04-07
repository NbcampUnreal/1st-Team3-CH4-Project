#include "Item/FoodCoinItem/FoodCoinItem.h"

AFoodCoinItem::AFoodCoinItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFoodCoinItem::BeginPlay()
{
	Super::BeginPlay();

}

void AFoodCoinItem::ActivateItem()
{
	UE_LOG(LogTemp, Warning, TEXT("fruit ate"));
}