#include "Item/ConsumableItem/PowerUpItem.h"
#include "GameFramework/Character.h"
#include "Item/ConsumableItem/PowerUpManagerComponent.h"

APowerUpItem::APowerUpItem()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>NiagaraEffectAsset(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_2.NS_Pickup_2"));
	if (NiagaraEffectAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraEffectAsset.Object);
	}

}


void APowerUpItem::ActivateItem_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("[ActiItemPower] ActivateItem_Implementation called"));

	if (!TargetActor) return;

	ACharacter* Player = Cast<ACharacter>(TargetActor);
	if (Player)
	{
		UPowerUpManagerComponent* PowerUpComp = Player->FindComponentByClass<UPowerUpManagerComponent>();
		if (PowerUpComp)
		{
			//Add Player To the list(PoweredUpPlayer)
			PowerUpComp->AddPoweredUpPlayer(Player);
			UE_LOG(LogTemp, Warning, TEXT("PowerUp Applied to : %s"), *Player->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No PowerUpManagerComponent found on %s"), *Player->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[powerupactiv]No player"));
	}
	
}
