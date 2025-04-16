#include "Character/NewPlayerState.h"

#include "Controller/NewPlayerController.h"
#include "GameState/NewGS.h"
#include "UI/ScoreBoardWidget.h"
#include "Net/UnrealNetwork.h"

ANewPlayerState::ANewPlayerState()
	:PlayerScore(0)
{
	bReplicates = true;
}

void ANewPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerScore);
	DOREPLIFETIME(ThisClass, PlayerIndex);
}


void ANewPlayerState::AddScore(int32 Amount)
{
	if (HasAuthority())
	{
		PlayerScore += Amount;
		OnRep_PlayerScore();
	}
}

void ANewPlayerState::SetScore(int32 InScore)
{
	if (HasAuthority())
	{
		PlayerScore = InScore;
		OnRep_PlayerScore();
	}
}

void ANewPlayerState::OnRep_PlayerScore()
{
	ANewGS* NewGS = Cast<ANewGS>(GetWorld()->GetGameState());
	if (IsValid(NewGS) && (NewGS->MatchState != EMatchState::Ending))
	{
		if (ANewPlayerController* NewPC = Cast<ANewPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			Cast<UScoreBoardWidget>(NewPC->GetScoreWidget())->UpdateScoreBoard();
		}		
	}
}

void ANewPlayerState::OnRep_PlayerIndex()
{
}
