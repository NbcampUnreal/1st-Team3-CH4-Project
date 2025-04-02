#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "CoinItem.generated.h"


UCLASS()
class FOODRUMBLE_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()
	
	virtual void OnOverlap(AActor* OverlapActor) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
