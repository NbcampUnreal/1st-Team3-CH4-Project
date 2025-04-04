#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "FoodCoinItem.generated.h"


UCLASS()
class FOODRUMBLE_API AFoodCoinItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AFoodCoinItem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void ActivateItem() override;

};
