#include "MapObjects/FRBreakableObject.h"
#include "Components/BoxComponent.h"
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

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComp->SetupAttachment(RootComp);
}

void AFRBreakableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFRBreakableObject::UpdateHitCount()
{
	OnHit();
	CurrentHitCount++;

	if (CurrentHitCount >= HitCountToBreakeObj && !bIsBroken)
	{
		if (IsValid(PoolManager))
		{			
			if (IsValid(ObjSpawner))
			{
				OnBroken();				
				PoolManager->ReturnToPool(this);
				ObjSpawner->NotifyObjReturned(ObjIndex);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No ObjSpawner"))
			}
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


