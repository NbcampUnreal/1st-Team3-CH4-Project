

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NewCharacter.generated.h"

class UCameraComponent;
class USkeletameshComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerCoinComponent;

UCLASS()
class FOODRUMBLE_API ANewCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANewCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


#pragma region Overrides Character

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

#pragma endregion

#pragma region PlayerCharacter Components

public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }

	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Components")
	TObjectPtr<UCameraComponent> Camera;
#pragma endregion

#pragma region Costume
public:
	UFUNCTION()
	void OnRep_CostumeChanged();

	void ApplyCostume();

	UFUNCTION(Server,Reliable)
	void ServerRPCSetRandomCostume();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Components")
	TObjectPtr<USkeletalMeshComponent> Face;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Components")
	TObjectPtr<USkeletalMeshComponent> Shirts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Components")
	TObjectPtr<USkeletalMeshComponent> Pants;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Components")
	TObjectPtr<USkeletalMeshComponent> Accessory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Components")
	TObjectPtr<USkeletalMeshComponent> Hair;

	UPROPERTY(ReplicatedUsing = OnRep_CostumeChanged)
	int32 FaceIndex;

	UPROPERTY(ReplicatedUsing = OnRep_CostumeChanged)
	int32 ShirtsIndex;

	UPROPERTY(ReplicatedUsing = OnRep_CostumeChanged)
	int32 PantsIndex;

	UPROPERTY(ReplicatedUsing = OnRep_CostumeChanged)
	int32 AccessoryIndex;

	UPROPERTY(ReplicatedUsing = OnRep_CostumeChanged)
	int32 HairIndex;
#pragma endregion

#pragma region Attack

public:
	void CheckAttackHit();
	
	UFUNCTION()
	void OnDeath();

protected:
	UFUNCTION(Server,Reliable)
	void ServerRPCAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCDrawDebugSphere(const FColor& DrawColor, FVector TraceStart, FVector TraceEnd, FVector Forward);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCRespawnCharacter();

	UFUNCTION()
	void OnRep_CanAttack();

	void PlayMeleeAttackMontage();

	UFUNCTION()
	void StopMoveWhenAttacked();

	void CanMoveTimerElapsed();

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage>AttackMontage;

	UPROPERTY(ReplicatedUsing = OnRep_CanAttack)
	bool bCanAttack;

	float AttackMontagePlayTime;

	FTimerHandle StopMoveHandle;
#pragma endregion

#pragma region Guard

public:
	void CheckGuard();

	UFUNCTION(Server, Reliable)
	void ServerRPCGuard();

	UFUNCTION(Server, Reliable)
	void ServerRPCGuardEnd();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCGuard();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCGuardEnd();

	UFUNCTION()
	void OnRep_IsInvincible();

	void PlayGuardMontage();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> GuardMontage;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsInvincible)
	bool bIsInvincible;
#pragma endregion

#pragma region Input
private:
	void HandleMoveInput(const FInputActionValue& InValue);

	void HandleLookInput(const FInputActionValue& InValue);

	void HandleAttackInput(const FInputActionValue& InValue);

	void HandleGuardInputStart(const FInputActionValue& InValue);

	void HandleGuardInputEnd(const FInputActionValue& InValue);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	TObjectPtr<UInputAction> GuardAction;

#pragma endregion

#pragma region CollectItem
	TObjectPtr<UPlayerCoinComponent> CollectCoin;

#pragma endregion

#pragma region RandomItem
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Costume")
	TArray<TObjectPtr<USkeletalMesh>> RandomFace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Costume")
	TArray<TObjectPtr<USkeletalMesh>> RandomShirts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Costume")
	TArray<TObjectPtr<USkeletalMesh>> RandomPants;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Costume")
	TArray<TObjectPtr<USkeletalMesh>> RandomAccessory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|Costume")
	TArray<TObjectPtr<USkeletalMesh>> RandomHair;

#pragma endregion
};
