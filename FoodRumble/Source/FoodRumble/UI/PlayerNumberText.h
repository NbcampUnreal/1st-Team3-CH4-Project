

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerNumberText.generated.h"

class UTextBlock;

UCLASS()
class FOODRUMBLE_API UPlayerNumberText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerNumberText(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	AActor* GetOwningActor() const { return OwningActor; }

	void SetOwningActor(AActor* InOwngingACtor) { OwningActor = InOwngingACtor; }

	UFUNCTION()
	void SetPlayerNumber(int32 InIndex);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNumberText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> OwningActor;
};
