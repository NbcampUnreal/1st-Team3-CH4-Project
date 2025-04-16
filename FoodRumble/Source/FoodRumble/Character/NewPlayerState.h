

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NewPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FOODRUMBLE_API ANewPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ANewPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() { return PlayerScore; }

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerIndex() { return PlayerIndex; }

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);	

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 InScore);

	UFUNCTION()
	void OnRep_PlayerScore();

	UFUNCTION()
	void OnRep_PlayerIndex();

public:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerIndex)
	int32 PlayerIndex;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore)
	int32 PlayerScore;

};
