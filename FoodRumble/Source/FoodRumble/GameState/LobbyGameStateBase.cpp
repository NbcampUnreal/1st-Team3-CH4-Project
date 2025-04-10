#include "GameState/LobbyGameStateBase.h"

#include "Character/LobbyCharacter.h"

#include "Kismet/GameplayStatics.h"

void ALobbyGameStateBase::OnRep_UpdateUI()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		
	}
}
