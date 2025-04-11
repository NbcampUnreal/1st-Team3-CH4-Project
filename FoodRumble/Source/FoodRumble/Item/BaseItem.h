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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UNiagaraComponent* NiagaraComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Effect")
	//UStaticMeshComponent* BubbleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UDataTable* ItemDataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FName ItemRowName;



public:
	//for ovelap event
	UPROPERTY(BlueprintReadOnly)
	AActor* CachedActor;

	UFUNCTION()
	void StopPhysics();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivateItem(AActor* TargetActor);

	virtual void ActivateItem_Implementation(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyItem();

};
