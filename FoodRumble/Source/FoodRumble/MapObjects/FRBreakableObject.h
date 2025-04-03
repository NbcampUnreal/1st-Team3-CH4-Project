#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRBreakableObject.generated.h"

class USphereComponent;

UCLASS()
class FOODRUMBLE_API AFRBreakableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFRBreakableObject();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvnet,
		AController* EventInstigator,
		AActor* DamageCauser)
		override;

protected:

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

	

};
