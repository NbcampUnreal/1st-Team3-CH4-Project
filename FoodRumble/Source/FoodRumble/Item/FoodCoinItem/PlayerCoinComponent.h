#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCoinComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOODRUMBLE_API UPlayerCoinComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerCoinComponent();

	UFUNCTION(BlueprintCallable)
	void AddCoins(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveCoins(int32 Amount);
		
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCoins() const;


private:
	UPROPERTY(VisibleAnywhere)
	int32 CurrentCoins;
};
