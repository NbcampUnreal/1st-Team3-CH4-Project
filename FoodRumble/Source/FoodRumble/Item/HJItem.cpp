#include "Item/HJItem.h"

#include "Components/SphereComponent.h"

AHJItem::AHJItem()
	:ScoreValue(10)
{ 
	PrimaryActorTick.bCanEverTick = false;
		
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collsion"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

