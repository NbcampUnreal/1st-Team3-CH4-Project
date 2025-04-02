#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class FOODRUMBLE_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseItem();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
