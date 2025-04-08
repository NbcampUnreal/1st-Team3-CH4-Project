#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BaseItem.generated.h"

class USphereComponent;
class UNiagaraComponent;
class ASpawnVolume;
UCLASS()
class FOODRUMBLE_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:

	ABaseItem();

protected:

	virtual void BeginPlay() override;
	////after spawning item
	//UPROPERTY()
	//ASpawnVolume* OwnerSpawnVolume;
	//UPROPERTY()
	//FVector MySpawnLocation;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UNiagaraComponent* NiagaraComponent;

public:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	virtual void ActivateItem();

	virtual void DestroyItem();

};
