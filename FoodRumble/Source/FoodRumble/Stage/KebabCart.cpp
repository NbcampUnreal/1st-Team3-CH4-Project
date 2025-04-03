#include "KebabCart.h"

AKebabCart::AKebabCart()
	: MoveSpeed(4000.0f)
	, MoveDistance(1000.0f)
	, DelayBeforeMove(10.0f)
	, ElapsedTime(0.0f)
	, bHasMoved(false)
{
	PrimaryActorTick.bCanEverTick = true;
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
