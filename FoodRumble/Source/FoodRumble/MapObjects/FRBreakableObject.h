#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRBreakableObject.generated.h"

class USphereComponent;
class AFRObjectPoolingManager;

UCLASS()
class FOODRUMBLE_API AFRBreakableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRBreakableObject();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHitCount();
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetPoolManager(AFRObjectPoolingManager* CurrentPoolManager);
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual void ResetObject();
	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawned();
	UFUNCTION(BlueprintImplementableEvent)
	void OnBroken();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HitCountToBreakeObj;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<USceneComponent> RootComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BrokenObj|Components")
	TObjectPtr<USphereComponent> SphereComp;
		
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHitCount;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsBroken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AFRObjectPoolingManager> PoolManager;

	

};
