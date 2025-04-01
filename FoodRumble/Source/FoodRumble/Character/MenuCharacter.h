

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MenuCharacter.generated.h"

UCLASS()
class FOODRUMBLE_API AMenuCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMenuCharacter();

protected:
	virtual void BeginPlay() override;
};
