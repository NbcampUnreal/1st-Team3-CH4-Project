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
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnRandom();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void NotifyObjReturned(int32 Index);
		
protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TObjectPtr<AFRObjectPoolingManager> PoolManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TObjectPtr<AActor>> SpawnPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner", Transient)
	TArray<TObjectPtr<AActor>> SpawnedObj;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float InitialDelay;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval;

	FTimerHandle SpawnTimerHandle;
	bool bIsSpawnPaused;
	
};
