#include "Character/NewAnimInstanceBase.h"

#include "Character/NewCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNewAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(GetOwningActor());
	if (IsValid(OwnerCharacter))
	{
		OwnerCharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UNewAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(OwnerCharacter) || !IsValid(OwnerCharacterMovementComponent))
	{
		return;
	}
	Velocity = OwnerCharacterMovementComponent->Velocity;
	GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();
	bShouldMove = (!(OwnerCharacterMovementComponent->GetCurrentAcceleration().IsNearlyZero()) && (3.f < GroundSpeed));
	bIsFalling = OwnerCharacterMovementComponent->IsFalling();
}

void UNewAnimInstanceBase::AnimNotify_CheckAttackHit()
{
	ANewCharacter* NewPlayerCharacter = Cast<ANewCharacter>(OwnerCharacter);
	if (IsValid(NewPlayerCharacter))
	{
		NewPlayerCharacter->CheckAttackHit();
	}
}
