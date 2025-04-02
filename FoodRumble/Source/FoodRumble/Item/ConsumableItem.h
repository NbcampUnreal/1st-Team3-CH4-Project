#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConsumableItem.generated.h"

UCLASS()
class FOODRUMBLE_API AConsumableItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AConsumableItem();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
