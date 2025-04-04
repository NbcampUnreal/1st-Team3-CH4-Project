

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KebabCart.generated.h"

UCLASS()
class FOODRUMBLE_API AKebabCart : public AActor
{
	GENERATED_BODY()
	
public:
	AKebabCart();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDistance;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DelayBeforeMove;

private:
	
	FVector StartLocation;
	float ElapsedTime;
	bool bHasMoved;
	float TimeSinceMoved;
};
