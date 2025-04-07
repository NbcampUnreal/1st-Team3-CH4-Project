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


	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
