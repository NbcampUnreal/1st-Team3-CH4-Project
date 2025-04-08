

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveLevel.generated.h"

/**
 * 
 */
UCLASS()
class FOODRUMBLE_API USaveLevel : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite)
	bool bIsLevel2Lock;
	UPROPERTY(BlueprintReadWrite)
	bool bIsLevel3Lock;
	UPROPERTY(BlueprintReadWrite)
	bool bIsLevel4Lock;
	
	/*UPROPERTY(BlueprintReadWrite)
	bool bIsRestart;*/
};
