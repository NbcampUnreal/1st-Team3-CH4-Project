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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	USphereComponent* CollisionSphere;
public:	
	UFUNCTION()
	virtual void OnOverlap(AActor* OverlapActor);

	virtual void ActivateItem();
	
	virtual void DestroyItem();

};
