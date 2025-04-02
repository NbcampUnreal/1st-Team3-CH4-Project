#include "Item/ConsumableItem/ConsumableItem.h"

AConsumableItem::AConsumableItem()
{



}


void AConsumableItem::OnOverlap(AActor* OverlapActor)
{
	ActivateItem();
	DestroyItem();
}
void AConsumableItem::ActivateItem()
{

}
void AConsumableItem::DestroyItem()
{

}


