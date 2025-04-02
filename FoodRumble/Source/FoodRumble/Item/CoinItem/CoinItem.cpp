#include "Item/CoinItem/CoinItem.h"

ACoinItem::ACoinItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/YJ_Item/Asset/Coin/source/coins_low.coins_low"));
	if (StaticMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void ACoinItem::OnOverlap(AActor* OverlapActor)
{
	ActivateItem();
	DestroyItem();
}
void ACoinItem::ActivateItem()
{

}
void ACoinItem::DestroyItem()
{

}