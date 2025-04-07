#include "Item/ConsumableItem/PowerUpItem.h"


APowerUpItem::APowerUpItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>NiagaraEffectAsset(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_2.NS_Pickup_2"));
	if (NiagaraEffectAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraEffectAsset.Object);
	}

}


void APowerUpItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

}
void APowerUpItem::ActivateItem()
{

}
void APowerUpItem::DestroyItem()
{

}
