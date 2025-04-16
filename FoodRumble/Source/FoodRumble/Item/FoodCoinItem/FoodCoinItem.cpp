#include "Item/FoodCoinItem/FoodCoinItem.h"
#include "Item/FoodCoinItem/PlayerCoinComponent.h"
#include "Item/ItemSpawnRow.h"

AFoodCoinItem::AFoodCoinItem()
{
	MeshComponent->SetSimulatePhysics(true);
	/*MeshComponent->SetEnableGravity(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	MeshComponent->BodyInstance.bUseCCD = true;*/
}


void AFoodCoinItem::ActivateItem_Implementation(AActor* TargetActor)
{
	if (ItemDataTable && ItemRowName != NAME_None)
	{

		const FItemSpawnRow* Row = ItemDataTable->FindRow<FItemSpawnRow>(ItemRowName, TEXT("Finding CoinItem"));
		if (Row)
		{
			UPlayerCoinComponent* CoinComponent = TargetActor->FindComponentByClass<UPlayerCoinComponent>();
			if (CoinComponent)
			{
				int32 CoinAmount = FMath::TruncToInt(Row->ItemScore);
				CoinComponent->AddCoins(CoinAmount);
				UE_LOG(LogTemp, Error, TEXT("%d Food Item added to player"), CoinAmount);
				UE_LOG(LogTemp, Error, TEXT("total food item : %d"), CoinComponent->GetCurrentCoins());
			}

		}

	}
}
