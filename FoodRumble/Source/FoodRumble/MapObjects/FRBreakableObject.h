#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRBreakableObject.generated.h"

class UBoxComponent;
class AFRObjectPoolingManager;
class AFRObjectSpawner;

UCLASS()
class FOODRUMBLE_API AFRBreakableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRBreakableObject();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable)
	void UpdateHitCount();
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetPoolManager(AFRObjectPoolingManager* CurrentPoolManager);
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void ResetObject();
	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawned();
	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();
	UFUNCTION(BlueprintImplementableEvent)
	void OnBroken();

	UFUNCTION()
	void OnRep_Broken();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnHit();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitCountToBreakeObj;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<USceneComponent> RootComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<UBoxComponent> BoxComp;
	TObjectPtr<AFRObjectPoolingManager> PoolManager;
	int32 ObjIndex;
	TObjectPtr<AFRObjectSpawner> ObjSpawner;
		
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Broken)
	bool bIsBroken;

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "BreakableObject")
	int32 CurrentHitCount;
	
	
};
