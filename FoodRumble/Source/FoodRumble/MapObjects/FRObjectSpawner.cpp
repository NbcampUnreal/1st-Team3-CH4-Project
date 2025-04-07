#include "MapObjects/FRObjectSpawner.h"
#include "FRObjectPoolingManager.h"
#include "FRBreakableObject.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AFRObjectSpawner::AFRObjectSpawner()
	:InitialDelay(2.0f),
	SpawnInterval(10.0f),
	bIsSpawnPaused(false)
{
	PrimaryActorTick.bCanEverTick = true;

}

AActor* AFRObjectSpawner::SpawnAtIndex(int32 Index)
{
	if (SpawnPoints.IsValidIndex(Index) && IsValid(SpawnPoints[Index]))
	{
		if (!SpawnedObj.IsValidIndex(Index) || !IsValid(SpawnedObj[Index]))
		{
			SpawnedObj.SetNum(Index + 1);

			if (IsValid(PoolManager))
			{
				TObjectPtr<AActor> SpawnedActor = PoolManager->GetPooledObject();

				if (IsValid(SpawnedActor))
				{
					FVector Location = SpawnPoints[Index]->GetActorLocation();
					FRotator Rotation = SpawnPoints[Index]->GetActorRotation();

					SpawnedActor->SetActorLocation(Location);
					SpawnedActor->SetActorRotation(Rotation);

					TObjectPtr<AFRBreakableObject> BreakableObj = Cast<AFRBreakableObject>(SpawnedActor);

					if (IsValid(BreakableObj))
					{
						BreakableObj->ResetObject();
						BreakableObj->OnSpawned();
						BreakableObj->SetPoolManager(PoolManager);
						BreakableObj->ObjSpawner = this;
						BreakableObj->ObjIndex = Index;
					}

					SpawnedObj[Index] = SpawnedActor;
					SpawnedActor->SetActorHiddenInGame(false);
					SpawnedActor->SetActorEnableCollision(true);

					return SpawnedActor;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No Object in Pool"));
					return nullptr;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No PoolManager %s"), *GetName());
				return nullptr;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn point %d is full"), Index);
			return nullptr;
		}		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error Index: %d"), Index);
		return nullptr;
	}
}

void AFRObjectSpawner::SpawnRandom()
{
	TArray<int32> EmptyPoint;

	for (int32 i = 0; i < SpawnPoints.Num(); ++i)
	{
		if (!IsValid(SpawnPoints[i])) continue;

		bool bIsOccupied = SpawnedObj.IsValidIndex(i) && IsValid(SpawnedObj[i]);

		if (!bIsOccupied)
		{
			EmptyPoint.Add(i);
		}
	}

	if (EmptyPoint.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty spawn points."));
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		bIsSpawnPaused = true;
		return;
	}	
	
	if (SpawnPoints.Num() == 0) return;

	int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
	SpawnAtIndex(RandomIndex);
}

void AFRObjectSpawner::NotifyObjReturned(int32 Index)
{
	if (SpawnedObj.IsValidIndex(Index))
	{
		SpawnedObj[Index] = nullptr;
	}

	if (bIsSpawnPaused)
	{
		UE_LOG(LogTemp, Log, TEXT("Empty slot opened. Resuming spawn."));
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&AFRObjectSpawner::SpawnRandom,
			SpawnInterval,
			true
		);

		bIsSpawnPaused = false;
	}
}

void AFRObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	bIsSpawnPaused = false;
	
	SpawnedObj.SetNum(SpawnedObj.Num());

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AFRObjectSpawner::SpawnRandom,
		SpawnInterval,
		true, InitialDelay);

}