

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

protected:
	// 이동 관련 설정값
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDistance;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DelayBeforeMove;

private:
	// 내부 상태
	FVector StartLocation;
	float ElapsedTime;
	bool bHasMoved;
};
