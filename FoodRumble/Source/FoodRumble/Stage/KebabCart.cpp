#include "KebabCart.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AKebabCart::AKebabCart()
	: MoveSpeed(1750.0f)
	, MoveDistance(3750.0f)
	, DelayBeforeMove(10.0f)
	, ElapsedTime(0.0f)
	, bHasMoved(false)
	, TimeSinceMoved(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true); // 꼭 충돌 활성화!
}

void AKebabCart::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void AKebabCart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasMoved)
	{
		TimeSinceMoved += DeltaTime;
		if (TimeSinceMoved >= 7.0f)
		{
			DestroyKebab(); // 7초 후 사라짐
		}
		return;
	}

	ElapsedTime += DeltaTime;

	if (ElapsedTime < DelayBeforeMove)
	{
		return;
	}

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Y += MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	float TraveledDistance = FMath::Abs(CurrentLocation.Y - StartLocation.Y);
	if (TraveledDistance >= MoveDistance)
	{
		bHasMoved = true;
	}
}



void AKebabCart::DestroyKebab()
{
	Destroy();
}
