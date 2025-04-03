#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
UCLASS()
class FOODRUMBLE_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem(TSubclassOf<AActor> ItemClass);

};
