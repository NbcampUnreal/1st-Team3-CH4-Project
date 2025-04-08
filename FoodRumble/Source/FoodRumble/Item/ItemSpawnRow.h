#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.generated.h"


USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemScore;
};