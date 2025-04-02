#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BaseItem.generated.h"

class USphereComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	USphereComponent* CollisionSphere;


public:	
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	virtual void ActivateItem();
	
	virtual void DestroyItem();

};
