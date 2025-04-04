#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRBreakableObject.h"
#include "FRObjectPoolingManager.generated.h"

UCLASS()
class FOODRUMBLE_API AFRObjectPoolingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRObjectPoolingManager();

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual void IntializePool();

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual AFRBreakableObject* GetPooledObject();
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	virtual void ReturnToPool(AFRBreakableObject* Object);
	 
protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooling")
	TSubclassOf<AFRBreakableObject> BreakableObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooling")
	int32 InitialPoolSize;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooling")
	TArray<AFRBreakableObject*> ObjectPool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<AActor*> SpawnPoints;

};
