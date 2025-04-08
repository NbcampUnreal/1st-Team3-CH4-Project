#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem/ConsumableItem.h"
#include "BarrierItem.generated.h"


UCLASS()
class FOODRUMBLE_API ABarrierItem : public AConsumableItem
{
	GENERATED_BODY()


public:
	ABarrierItem();
	virtual void ActivateItem_Implementation(AActor* TargetActor) override;
};
