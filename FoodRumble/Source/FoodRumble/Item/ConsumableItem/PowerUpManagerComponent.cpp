#include "Item/ConsumableItem/PowerUpManagerComponent.h"
#include "GameFramework/Character.h"

UPowerUpManagerComponent::UPowerUpManagerComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

//called when player overlapped with powerupItem / AddPoweredUpPlayer
//if timer ends player is automatically removed from PoweredUpPlayers list 
void UPowerUpManagerComponent::AddPoweredUpPlayer(ACharacter* Player)
{
	UE_LOG(LogTemp, Error, TEXT("[PowerUpManager] AddPoweredUpPlayer Called for: %s"), *Player->GetName());
	if (!Player) return;

	for (FPowerUpInfo& Info : PoweredUpPlayers)
	{
		//if player is already in powered Up state-> clear timer and restart the timer
		if (Info.Character == Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Character ate powerupItem again : %s"), *Player->GetName());
			GetWorld()->GetTimerManager().ClearTimer(Info.ExpireTimer);
			GetWorld()->GetTimerManager().SetTimer(Info.ExpireTimer, FTimerDelegate::CreateUObject(this, &UPowerUpManagerComponent::RemovePoweredUpPlayer, Player), 10.f, false);
			return;
		}
	}
	//if player is not in powered up state, and player and set timer
	FPowerUpInfo NewInfo;
	NewInfo.Character = Player;
	UE_LOG(LogTemp, Warning, TEXT("Character ate powerupItem(first) : %s"), *Player->GetName());
	GetWorld()->GetTimerManager().SetTimer(NewInfo.ExpireTimer, FTimerDelegate::CreateUObject(this, &UPowerUpManagerComponent::RemovePoweredUpPlayer, Player), 10.f, false);
	PoweredUpPlayers.Add(NewInfo);
}

//return if this player ate and is effected by PowerUpItem or not
bool UPowerUpManagerComponent::IsPoweredUp(ACharacter* Player) const
{
	for (const FPowerUpInfo& Info : PoweredUpPlayers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Character: %s / in PoweredUpPlayers : %s"), *Player->GetName(), *Info.Character->GetName());
		if (Info.Character == Player)
		{
			return true;
		}
	}
	return false;
}

//if timer ended, remove player
void UPowerUpManagerComponent::RemovePoweredUpPlayer(ACharacter* Player)
{
	PoweredUpPlayers.RemoveAll([Player](const FPowerUpInfo& Info)
		{ 
			return Info.Character == Player;
		}
	);
}