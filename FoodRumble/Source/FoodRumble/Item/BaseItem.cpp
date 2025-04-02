#include "Item/BaseItem.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

