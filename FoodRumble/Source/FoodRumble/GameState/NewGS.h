

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NewGS.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	None, 
	Waiting,
	Playing,
	Ending,
	End,
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerScore;
};

UCLASS()
class FOODRUMBLE_API ANewGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 TotalPlayerControllerCount = 0;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	EMatchState MatchState = EMatchState::Waiting;
};
