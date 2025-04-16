#include "MapObjects/FRBreakableObject.h"
#include "Components/BoxComponent.h"
#include "FRObjectPoolingManager.h"
#include "FRObjectSpawner.h"
#include "Net/UnrealNetwork.h"

AFRBreakableObject::AFRBreakableObject()
	:HitCountToBreakeObj(3),
	CurrentHitCount(0),
	bIsBroken(false)
	
{
	PrimaryActorTick.bCanEverTick = false;

	
	bReplicates = true;
	SetReplicateMovement(true);
	
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

void AFRBreakableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFRBreakableObject, bIsBroken);
	DOREPLIFETIME(AFRBreakableObject, CurrentHitCount);
}

void AFRBreakableObject::UpdateHitCount()
{
	if (HasAuthority())
	{
		Multicast_OnHit();
		CurrentHitCount++;

		if (CurrentHitCount >= HitCountToBreakeObj && !bIsBroken)
		{
			if (IsValid(PoolManager))
			{
				if (IsValid(ObjSpawner))
				{
					bIsBroken = true;
					SetActorHiddenInGame(true);
					SetActorEnableCollision(false);

					bIsBroken = true;

					OnBroken();
					PoolManager->ReturnToPool(this);
					ObjSpawner->NotifyObjReturned(ObjIndex);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No ObjSpawner"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No PoolManager"));
			}
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

void AFRBreakableObject::OnRep_Broken()
{
	SetActorHiddenInGame(bIsBroken);
	SetActorEnableCollision(!bIsBroken);

	if (bIsBroken)
	{
		OnBroken();
	}
}

void AFRBreakableObject::Multicast_OnHit_Implementation()
{
	OnHit();
}


