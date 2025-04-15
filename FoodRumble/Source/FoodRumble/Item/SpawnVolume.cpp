#include "Item/SpawnVolume.h"
#include "Item/BaseItem.h"

ASpawnVolume::ASpawnVolume()
{
	bReplicates = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;
}


void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		StartSpawning();
	}
}


void ASpawnVolume::StartSpawning()
{
	float RandomSpawnTime = FMath::FRandRange(3.0f, 6.0f);

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawnVolume::SpawnRandomItem,
		RandomSpawnTime,
		false
	);
}



//returns vector from the center of spawningbox
FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	//y
	float Y = FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y);
	//z
	float Z = FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z);
	//x
	float X = FMath::FRandRange(-BoxExtent.X, BoxExtent.X);

	FVector NewLocation = FVector(BoxOrigin.X + X, BoxOrigin.Y + Y, BoxOrigin.Z + Z);

	return NewLocation;
}


//Spawn Random item
void ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			SpawnItem(ActualClass);
		}
	}

	StartSpawning();
}

//get all rows from itemDataTable
FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable) return nullptr;

	TArray<FItemSpawnRow*> AllRows;

	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}
	const float RandValue = FMath::FRandRange(0.0f, TotalChance);


	float AccumulateChance = 0.0f;
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	return nullptr;
}


//spawns Item from ItemClass
void ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!HasAuthority()|| !ItemClass) return;

	FVector SpawnLocation = GetRandomPointInVolume();

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		SpawnLocation,
		FRotator::ZeroRotator
	);
	
	if (!SpawnedActor)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Item: %s"), *ItemClass->GetName());
		return;
	}
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}
