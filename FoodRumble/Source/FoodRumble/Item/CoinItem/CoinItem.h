#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "CoinItem.generated.h"


UCLASS()
class FOODRUMBLE_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoinItem();
	
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void ActivateItem() override;


	virtual void DestroyItem() override;
};
