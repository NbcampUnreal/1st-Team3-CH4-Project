#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
UCLASS()
class FOODRUMBLE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:

	ASpawnVolume();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomItem();


	FItemSpawnRow* GetRandomItem() const;
	void SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume();
	void StartSpawning();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UDataTable* ItemDataTable;

	FTimerHandle SpawnTimerHandle;

};
