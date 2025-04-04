#include "MapObjects/FRObjectSpawner.h"
#include "FRObjectPoolingManager.h"
#include "FRBreakableObject.h"

AFRObjectSpawner::AFRObjectSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

TObjectPtr<AActor> AFRObjectSpawner::SpawnAtIndex(int32 Index)
{
	if (SpawnPoints.IsValidIndex(Index) && IsValid(SpawnPoints[Index]))
	{
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
					BreakableObj->OnSpawned();
					BreakableObj->ResetObject();
				}

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
		UE_LOG(LogTemp, Warning, TEXT("Error Index: %d"), Index);
		return nullptr;
	}
}

TObjectPtr<AActor> AFRObjectSpawner::SpawnRandom()
{
	return TObjectPtr<AActor>();
}

void AFRObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}