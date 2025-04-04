#include "Item/ConsumableItem/BarrierItem.h"


ABarrierItem::ABarrierItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>NiagaraEffectAsset(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_4.NS_Pickup_4"));
	if (NiagaraEffectAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraEffectAsset.Object);
	}
}


void ABarrierItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

}
void ABarrierItem::ActivateItem()
{

}
void ABarrierItem::DestroyItem()
{

}
