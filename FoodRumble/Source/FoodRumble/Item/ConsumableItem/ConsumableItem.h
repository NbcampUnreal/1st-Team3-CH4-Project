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

	virtual void OnOverlap(AActor* OverlapActor) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
