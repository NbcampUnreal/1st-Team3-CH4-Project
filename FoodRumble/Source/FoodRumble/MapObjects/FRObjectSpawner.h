#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRObjectSpawner.generated.h"

class AFRObjectPoolingManager;
class AFRBreakableObject;

UCLASS()
class FOODRUMBLE_API AFRObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRObjectSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	AActor* SpawnAtIndex(int32 Index);
	
	//Spawn Random for boss stage?
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	AActor* SpawnRandom();

	UFUNCTION()
	void ClearSlot(int32 Index);

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TObjectPtr<AFRObjectPoolingManager> PoolManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TObjectPtr<AActor>> SpawnPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TObjectPtr<AActor>> SpawnedObj;
	
};
