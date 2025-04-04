#include "MapObjects/FRObjectPoolingManager.h"
#include "Kismet/GameplayStatics.h"

AFRObjectPoolingManager::AFRObjectPoolingManager()
	:InitialPoolSize(4)
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFRObjectPoolingManager::IntializePool()
{
	if (BreakableObject)
	{
		if (UWorld* World = GetWorld())
		{
			for (int32 i = 0; i < InitialPoolSize; i++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				AFRBreakableObject* NewObject = World->SpawnActor<AFRBreakableObject>(
					BreakableObject,
					FVector::ZeroVector, FRotator::ZeroRotator,
					SpawnParams
				);

				if (NewObject)
				{
					NewObject->SetActorHiddenInGame(true);
					NewObject->SetActorEnableCollision(false);
					ObjectPool.Add(NewObject);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Set on %s"), *GetName());
	}
}

AFRBreakableObject* AFRObjectPoolingManager::GetPooledObject()
{
	for (AFRBreakableObject* obj : ObjectPool)
	{
		if (IsValid(obj) && obj->IsHidden())
		{
			return obj;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No obj in pool for %s"), *GetName());

	return nullptr;
}

void AFRObjectPoolingManager::ReturnToPool(AFRBreakableObject* Object)
{
	if (!IsValid(Object)) return;

	Object->SetActorHiddenInGame(true);
	Object->SetActorEnableCollision(false);

}

void AFRObjectPoolingManager::BeginPlay()
{
	Super::BeginPlay();

	IntializePool();
}



