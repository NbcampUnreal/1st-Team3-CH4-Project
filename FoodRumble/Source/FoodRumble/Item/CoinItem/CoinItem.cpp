#include "Item/CoinItem/CoinItem.h"

ACoinItem::ACoinItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("/Game/YJ_Item/Asset/Coin/source/coins_low.coins_low"));
	if (StaticMeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void ACoinItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

}
void ACoinItem::ActivateItem()
{

}
void ACoinItem::DestroyItem()
{

}