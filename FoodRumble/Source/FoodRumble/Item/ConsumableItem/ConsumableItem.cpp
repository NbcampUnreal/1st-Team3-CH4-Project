#include "Item/ConsumableItem/ConsumableItem.h"

AConsumableItem::AConsumableItem()
{
	bReplicates = true;
	SetReplicates(true);

	NiagaraComponent->SetRelativeLocation(FVector(0.f, 0.f, -42.f));
}
