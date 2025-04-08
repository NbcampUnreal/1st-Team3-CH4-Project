#include "Item/ConsumableItem/SpeedUpItem.h"

ASpeedUpItem::ASpeedUpItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>NiagaraEffectAsset(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_3.NS_Pickup_3"));
	if (NiagaraEffectAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraEffectAsset.Object);
	}
}



void ASpeedUpItem::ActivateItem_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("[ActiItemSpeed] ActivateItem_Implementation called"));
	if (CachedActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("CachedActor name: %s"), *CachedActor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("[ActiItemSpeed] cached actor exists"));

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[ActiItemSpeed] CachedActor is null"));
	}
}
