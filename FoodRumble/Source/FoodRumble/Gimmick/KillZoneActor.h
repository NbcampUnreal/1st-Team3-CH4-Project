

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZoneActor.generated.h"

class UBoxComponent;

UCLASS()
class FOODRUMBLE_API AKillZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKillZoneActor();

	UFUNCTION()
	void OnOverlap
	(
		UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult
	);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USceneComponent>SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<UBoxComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	float CollisionRadius;

};
