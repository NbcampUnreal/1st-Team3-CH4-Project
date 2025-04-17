#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NewGM.generated.h"

class ANewPlayerController;
class ASpawnVolume;

UCLASS()
class FOODRUMBLE_API ANewGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer)override;

	virtual void Logout(AController* Existing) override;

	void OnCharacterDead(ANewPlayerController* InController);

	//for start game ui
	UFUNCTION()
	void CanStartGame() { bCanStartGame = true; }

	UFUNCTION()
	bool GetIsReady() { return bIsReady; }

private:
	UFUNCTION()
	void OnMainTimerElapsed();

	void NotifyToAllPlayer(const FString& NotificationString);

	void NotifyToAllPlayerScore();

	void NotifyToAllPlayerTime(const FString& NotificationString);

	UFUNCTION()
	void OnMainLoopTimerElapsed();

public:
	FTimerHandle MainTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WaitingTime = 10;

	int32 RemainWaitingTimeForPlaying = 10;

	int32 MinimumPlayerCountForPlaying = 2;

	//Game Sytem
	FTimerHandle MainLoopTimerHandle;

	int32 MainLoopPlayingTime = 60;
	int32 RemainMainLoopPlayingTime = 60;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<FVector> SpawnLocations;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ANewPlayerController>> TotalPlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ANewPlayerController>> DeadPlayerControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<ASpawnVolume> SpawnVolumeClass;

private:
	bool bCanStartGame;
	bool bIsReady;
};
