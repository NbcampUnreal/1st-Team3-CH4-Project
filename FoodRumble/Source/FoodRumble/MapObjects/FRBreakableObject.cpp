#include "MapObjects/FRBreakableObject.h"
#include "Components/SphereComponent.h"
#include "FRObjectPoolingManager.h"
#include "FRObjectSpawner.h"

AFRBreakableObject::AFRBreakableObject()
	:HitCountToBreakeObj(3),
	CurrentHitCount(0),
	bIsBroken(false)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComp->SetupAttachment(RootComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComp->SetupAttachment(RootComp);
}

void AFRBreakableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFRBreakableObject::UpdateHitCount()
{
	CurrentHitCount++;

	if (CurrentHitCount >= HitCountToBreakeObj && !bIsBroken)
	{
		if (IsValid(PoolManager))
		{			
			/*if (IsValid(ObjSpawner))
			{
				OnBroken();				
				PoolManager->ReturnToPool(this);
				ObjSpawner->ClearSlot(ObjIndex);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No ObjSpawner"))
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No PoolManager"))
		}
	}
}

void AFRBreakableObject::SetPoolManager(AFRObjectPoolingManager* CurrentPoolManager)
{
	PoolManager = CurrentPoolManager;
}


void AFRBreakableObject::ResetObject()
{
	CurrentHitCount = 0;
	bIsBroken = false;
}


