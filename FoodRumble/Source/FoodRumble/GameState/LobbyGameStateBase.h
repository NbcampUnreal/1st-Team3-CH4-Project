

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameStateBase.generated.h"

class ALobbyCharacter;

UCLASS()
class FOODRUMBLE_API ALobbyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnRep_UpdateUI();

private:
	UPROPERTY(ReplicatedUsing = OnRep_UpdateUI)
	TArray<ALobbyCharacter*> LobbyPlayerLists;
};
