

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FOODRUMBLE_API AMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuGameModeBase();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsEndLevel() { return bIsEndLevel; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetEndLevelTrue() { bIsEndLevel = true; }

private:
	bool bIsEndLevel;
};
