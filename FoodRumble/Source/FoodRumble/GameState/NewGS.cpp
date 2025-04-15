#include "GameState/NewGS.h"

#include "Net/UnrealNetwork.h"

void ANewGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, TotalPlayerControllerCount);
	DOREPLIFETIME(ThisClass, MatchState);
}
