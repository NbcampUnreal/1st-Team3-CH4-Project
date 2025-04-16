

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NewPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FOODRUMBLE_API ANewPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void ClientRPCShowScoreWidget();

	UFUNCTION(Client, Reliable)
	void ClientRPCShowEndGameWidget(int32 WinnerIndex);

	UUserWidget* GetScoreWidget() { return ScoreWidgetInstance; }

	void OnCharacterDead();

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FText NotificationText;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FText MainLoopTimerText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> NotificationTextUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UUserWidget> NotificationTextUIInstance;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UUserWidget> ScoreWidgetInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UUserWidget> EndGameWidgetInstance;
};
