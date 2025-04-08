#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerUpManagerComponent.generated.h"

class ACharacter;

USTRUCT()
struct FPowerUpInfo
{
	GENERATED_BODY()

	UPROPERTY()
	ACharacter* Character;

	FTimerHandle ExpireTimer;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOODRUMBLE_API UPowerUpManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPowerUpManagerComponent();

	UFUNCTION(BlueprintCallable)
	void AddPoweredUpPlayer(ACharacter* Player);

	UFUNCTION(BlueprintCallable)
	bool IsPoweredUp(ACharacter* Player) const;

private:
	UPROPERTY()
	TArray<FPowerUpInfo> PoweredUpPlayers;

	void RemovePoweredUpPlayer(ACharacter* Player);
		
};
