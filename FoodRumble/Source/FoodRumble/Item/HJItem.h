

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HJItem.generated.h"

class USphereComponent;

UCLASS()
class FOODRUMBLE_API AHJItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AHJItem();

	UFUNCTION()
	int32 GetScoreValue() const { return ScoreValue; }

protected:
	UPROPERTY(VisibleAnywhere)
	int32 ScoreValue;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

};