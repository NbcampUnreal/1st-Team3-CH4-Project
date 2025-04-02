#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ConsumableItem.generated.h"

UCLASS()
class FOODRUMBLE_API AConsumableItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	

	AConsumableItem();

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
