#include "Item/ConsumableItem/PowerUpManagerComponent.h"


UPowerUpManagerComponent::UPowerUpManagerComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

//AddPoweredUpPlayer
void UPowerUpManagerComponent::AddPoweredUpPlayer(ACharacter* Player)
{
	if (!Player) return;

	for (FPowerUpInfo& Info : PoweredUpPlayers)
	{
		if (Info.Character == Player)
		{
			GetWorld()->GetTimerManager().ClearTimer(Info.ExpireTimer);
			GetWorld()->GetTimerManager().SetTimer(Info.ExpireTimer, FTimerDelegate::CreateUObject(this, &UPowerUpManagerComponent::RemovePoweredUpPlayer, Player), 10.f, false);
			return;
		}
	}
	FPowerUpInfo NewInfo;
	NewInfo.Character = Player;

	GetWorld()->GetTimerManager().SetTimer(NewInfo.ExpireTimer, FTimerDelegate::CreateUObject(this, &UPowerUpManagerComponent::RemovePoweredUpPlayer, Player), 10.f, false);
	PoweredUpPlayers.Add(NewInfo);
}

//return if this player ate and is effected by PowerUpItem or not
bool UPowerUpManagerComponent::IsPoweredUp(ACharacter* Player) const
{
	for (const FPowerUpInfo& Info : PoweredUpPlayers)
	{
		if (Info.Character == Player)
		{
			return true;
		}
	}
	return false;
}

//
void UPowerUpManagerComponent::RemovePoweredUpPlayer(ACharacter* Player)
{
	PoweredUpPlayers.RemoveAll([Player](const FPowerUpInfo& Info)
		{
			return Info.Character == Player;
		}
	);
}