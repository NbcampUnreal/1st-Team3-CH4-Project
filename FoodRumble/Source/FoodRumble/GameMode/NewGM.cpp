#include "GameMode/NewGM.h"

#include "Character/NewPlayerState.h"
#include "Controller/NewPlayerController.h"
#include "GameState/NewGS.h"
#include "Item/SpawnVolume.h"

void ANewGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MainTimerHandle, this, &ThisClass::OnMainTimerElapsed, 1.f, true);

	RemainWaitingTimeForPlaying = WaitingTime;
	RemainMainLoopPlayingTime = MainLoopPlayingTime;	
}

void ANewGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ANewPlayerController* NewPC = Cast<ANewPlayerController>(NewPlayer);
	if (IsValid(NewPC))
	{
		TotalPlayerControllers.Add(NewPC);

		NewPC->NotificationText = FText::FromString(TEXT("connected to the game server"));	
		ANewPlayerState* NewPS = NewPC->GetPlayerState<ANewPlayerState>();
		if (IsValid(NewPS))
		{
			NewPS->PlayerIndex = TotalPlayerControllers.Num();
		}
	}
}

void ANewGM::Logout(AController* Existing)
{
	Super::Logout(Existing);

	ANewPlayerController* ExistingPC = Cast<ANewPlayerController>(Existing);
	if (IsValid(ExistingPC) && TotalPlayerControllers.Find(ExistingPC) != INDEX_NONE)
	{
		TotalPlayerControllers.Remove(ExistingPC);
		DeadPlayerControllers.Add(ExistingPC);
	}
}

void ANewGM::OnMainTimerElapsed()
{
	ANewGS* NewGS = GetGameState<ANewGS>();
	if (!IsValid(NewGS))
	{
		return;
	}

	switch (NewGS->MatchState)
	{
	case EMatchState::None:
		break;
	case EMatchState::Waiting:
		{
			FString NotificationString = FString::Printf(TEXT(""));

			if (TotalPlayerControllers.Num() < MinimumPlayerCountForPlaying)
			{
				NotificationString = FString::Printf(TEXT("Wait another player"));
				RemainWaitingTimeForPlaying = WaitingTime;
			}
			else
			{
				NotificationString = FString::Printf(TEXT("Wait %d seconds for playing"), RemainWaitingTimeForPlaying);

				RemainWaitingTimeForPlaying--;
			}
			if (RemainWaitingTimeForPlaying <= 0)
			{
				NotificationString = FString::Printf(TEXT("Play!"));
				NewGS->MatchState = EMatchState::Playing;
			}

			NotifyToAllPlayer(NotificationString);
			break;
		}
	case EMatchState::Playing:
		{
			NotifyToAllPlayerScore();
			GetWorldTimerManager().SetTimer(MainLoopTimerHandle, this, &ThisClass::OnMainLoopTimerElapsed, MainLoopPlayingTime, false);
			RemainMainLoopPlayingTime--;

			FString TimerString = FString::Printf(TEXT("Remain Time : %d s"), RemainMainLoopPlayingTime);

			if (RemainMainLoopPlayingTime <= 0)
			{
				NewGS->MatchState = EMatchState::Ending;
			}

			if (IsValid(SpawnVolumeClass))
			{				
				ASpawnVolume* SpawnVolumeInstance = GetWorld()->SpawnActor<ASpawnVolume>(SpawnVolumeClass, FVector(0.f, 0.f, 0.f), FRotator::ZeroRotator);
				//SpawnVolume->StartSpawning();				
			}
			NotifyToAllPlayerTime(TimerString);
			break;
		}
	case EMatchState::Ending:
		{			
			//stop game			

			//check winner
			int32 WinnerIndex = -1;
			int32 WinnerScore = 0;
			for (auto PC : TotalPlayerControllers)	
			{
				ANewPlayerState* NewPS = Cast<ANewPlayerState>(PC->PlayerState);
				if (IsValid(NewPS))
				{
					if (WinnerScore <= NewPS->GetPlayerScore())
					{
						WinnerScore = NewPS->GetPlayerScore();
						WinnerIndex = NewPS->GetPlayerIndex();
					}
				}				
			}
			//client RPC
			for (auto PC : TotalPlayerControllers)
			{
				PC->ClientRPCShowEndGameWidget(WinnerIndex);
			}
			break;
		}
	case EMatchState::End:
		break;
	default:
		break;
	}
}

void ANewGM::NotifyToAllPlayer(const FString& NotificationString)
{
	for (auto PC : TotalPlayerControllers)
	{
		PC->NotificationText = FText::FromString(NotificationString);
	}

	for (auto DeadPC : DeadPlayerControllers)
	{
		DeadPC->NotificationText = FText::FromString(NotificationString);
	}
}

void ANewGM::NotifyToAllPlayerScore()
{
	for (auto PC : TotalPlayerControllers)
	{
		PC->ClientRPCShowScoreWidget();
	}
}

void ANewGM::NotifyToAllPlayerTime(const FString& NotificationString)
{
	for (auto PC : TotalPlayerControllers)
	{
		PC->MainLoopTimerText = FText::FromString(NotificationString);
	}
}

void ANewGM::OnMainLoopTimerElapsed()
{
	//Game End
	UE_LOG(LogTemp, Warning, TEXT("End Game"));
}
