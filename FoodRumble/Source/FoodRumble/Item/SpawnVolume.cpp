#include "Item/SpawnVolume.h"


ASpawnVolume::ASpawnVolume()
{
 
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
}


FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

void ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return;
	GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);

}
