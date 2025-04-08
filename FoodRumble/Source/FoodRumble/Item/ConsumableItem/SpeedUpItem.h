#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem/ConsumableItem.h"
#include "GameFramework/Actor.h"
#include "SpeedUpItem.generated.h"


UCLASS()
class FOODRUMBLE_API ASpeedUpItem : public AConsumableItem
{
	GENERATED_BODY()

	
public:
	ASpeedUpItem();
	virtual void ActivateItem_Implementation(AActor* TargetActor) override;
};
