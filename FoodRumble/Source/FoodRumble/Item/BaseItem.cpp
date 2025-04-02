#include "Item/BaseItem.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetupAttachment(RootComponent);
	
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABaseItem::OnOverlap(AActor* OverlapActor)
{

}
void ABaseItem::ActivateItem()
{

}


void ABaseItem::DestroyItem()
{

}
