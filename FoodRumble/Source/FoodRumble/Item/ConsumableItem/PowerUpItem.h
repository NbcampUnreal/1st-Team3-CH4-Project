#pragma once

#include "CoreMinimal.h"
#include "Item/ConsumableItem/ConsumableItem.h"
#include "PowerUpItem.generated.h"


UCLASS()
class FOODRUMBLE_API APowerUpItem : public AConsumableItem
{
	GENERATED_BODY()
	
public:
	APowerUpItem(); 

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
