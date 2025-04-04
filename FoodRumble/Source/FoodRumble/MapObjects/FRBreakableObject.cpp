#include "MapObjects/FRBreakableObject.h"
#include "Components/SphereComponent.h"
#include "FRObjectPoolingManager.h"

AFRBreakableObject::AFRBreakableObject()
	:HitCountToBreakeObj(3),
	CurrentHitCount(0),
	bIsBroken(false)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

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
			OnBroken();
			PoolManager->ReturnToPool(this);
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


