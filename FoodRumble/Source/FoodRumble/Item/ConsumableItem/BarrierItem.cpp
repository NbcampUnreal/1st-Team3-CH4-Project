#include "Item/ConsumableItem/BarrierItem.h"


ABarrierItem::ABarrierItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>NiagaraEffectAsset(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_4.NS_Pickup_4"));
	if (NiagaraEffectAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraEffectAsset.Object);
	}
}

void ABarrierItem::ActivateItem_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("[ActiItemBarrier] ActivateItem_Implementation called"));

}
