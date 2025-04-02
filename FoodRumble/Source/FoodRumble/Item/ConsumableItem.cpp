#include "Item/ConsumableItem.h"

AConsumableItem::AConsumableItem()
{

	PrimaryActorTick.bCanEverTick = true;

}


void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();
	
}


void AConsumableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

