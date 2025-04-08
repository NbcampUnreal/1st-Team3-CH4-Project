#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem/ConsumableItem.h"
#include "PowerUpItem.generated.h"

class ACharacter;
UCLASS()
class FOODRUMBLE_API APowerUpItem : public AConsumableItem
{
	GENERATED_BODY()
	
public:
	APowerUpItem(); 
	virtual void ActivateItem_Implementation(AActor* TargetActor) override;
};
