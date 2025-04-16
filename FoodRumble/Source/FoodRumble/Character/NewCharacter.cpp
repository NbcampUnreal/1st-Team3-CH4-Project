#include "Character/NewCharacter.h"

#include "Item/HJItem.h"
#include "Item/FoodCoinItem/FoodCoinItem.h"
#include "Item/FoodCoinItem/PlayerCoinComponent.h"
#include "Controller/NewPlayerController.h"
#include "Character/NewPlayerState.h"

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"

ANewCharacter::ANewCharacter()
	:bCanAttack(true)
	, AttackMontagePlayTime(0.f)
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CollectCoin = CreateDefaultSubobject<UPlayerCoinComponent>(TEXT("CollectCoin"));

	Face = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	Face->SetupAttachment(GetMesh());
	
	Shirts = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shirts"));
	Shirts->SetupAttachment(GetMesh());
	
	Pants = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pants"));
	Pants->SetupAttachment(GetMesh());

	Accessory = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Accessory"));
	Accessory->SetupAttachment(GetMesh());

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
}

void ANewCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, FaceIndex);
	DOREPLIFETIME(ThisClass, ShirtsIndex);
	DOREPLIFETIME(ThisClass, PantsIndex);
	DOREPLIFETIME(ThisClass, AccessoryIndex);
	DOREPLIFETIME(ThisClass, HairIndex);
}


void ANewCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFoodCoinItem* Item = Cast<AFoodCoinItem>(OtherActor);

	if (Item && HasAuthority())
	{
		int32 Score = CollectCoin->GetCurrentCoins();

		ANewPlayerState* NewPS = Cast<ANewPlayerState>(GetPlayerState());
		if (IsValid(NewPS))
		{
			NewPS->SetScore(Score);
		}
		Item->Destroy();
	}
}


void ANewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveInput);

	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::HandleLookInput);

	EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);

	EIC->BindAction(AttackAction, ETriggerEvent::Started, this, &ThisClass::HandleAttackInput);
}

void ANewCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		checkf(IsValid(PC), TEXT("PlayerController is invalid"));

		UEnhancedInputLocalPlayerSubsystem* EILPS = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		checkf(IsValid(EILPS), TEXT("EnhancedInputLocalPlayerSubsystem is invalid"));

		EILPS->AddMappingContext(InputMappingContext, 0);		
	}
	if (HasAuthority())
	{
		ServerRPCSetRandomCostume();
	}
	else
	{
		ServerRPCSetRandomCostume();
	}

	if (IsValid(AttackMontage))
	{
		AttackMontagePlayTime = AttackMontage->GetPlayLength();
	}
}

void ANewCharacter::OnRep_CostumeChanged()
{
	ApplyCostume();
}

void ANewCharacter::ApplyCostume()
{
	//set costume
	if (RandomFace.IsValidIndex(FaceIndex))
	{
		Face->SetSkeletalMesh(RandomFace[FaceIndex]);
	}
	if (RandomShirts.IsValidIndex(ShirtsIndex))
	{
		Shirts->SetSkeletalMesh(RandomShirts[ShirtsIndex]);
	}
	if (RandomPants.IsValidIndex(PantsIndex))
	{
		Pants->SetSkeletalMesh(RandomPants[PantsIndex]);
	}
	if (RandomAccessory.IsValidIndex(AccessoryIndex))
	{
		Accessory->SetSkeletalMesh(RandomAccessory[AccessoryIndex]);
	}
	if (RandomHair.IsValidIndex(HairIndex))
	{
		Hair->SetSkeletalMesh(RandomHair[HairIndex]);
	}
}

void ANewCharacter::ServerRPCSetRandomCostume_Implementation()
{
	FaceIndex = RandomFace.IsEmpty() ? -1 : FMath::RandRange(0, RandomFace.Num() - 1);
	ShirtsIndex = RandomShirts.IsEmpty() ? -1 : FMath::RandRange(0, RandomShirts.Num() - 1);
	PantsIndex = RandomPants.IsEmpty() ? -1 : FMath::RandRange(0, RandomPants.Num() - 1);
	AccessoryIndex = RandomAccessory.IsEmpty() ? -1 : FMath::RandRange(0, RandomAccessory.Num() - 1);
	HairIndex = RandomHair.IsEmpty() ? -1 : FMath::RandRange(0, RandomHair.Num() - 1);

	ApplyCostume();
}

void ANewCharacter::CheckAttackHit()
{
	if (HasAuthority())
	{
		TArray<FHitResult> OutHitResults;
		TSet<ACharacter*> DamagedCharacters;
		FCollisionQueryParams Params(NAME_None, false, this);

		const float MeleeAttackRange = 50.f;
		const float MeleeAttackRadius = 50.f;
		const float MeleeAttackDamage = 10.f;

		const FVector Forward = GetActorForwardVector();
		const FVector Start = GetActorLocation() + Forward * GetCapsuleComponent()->GetScaledCapsuleRadius();
		const FVector End = Start + GetActorForwardVector() * MeleeAttackRange;

		bool bIsHitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ECC_Camera, FCollisionShape::MakeSphere(MeleeAttackRadius), Params);
		if (bIsHitDetected)
		{
			for (auto const& OutHitResult : OutHitResults)
			{
				ACharacter* DamagedCharacter = Cast<ACharacter>(OutHitResult.GetActor());
				if (IsValid(DamagedCharacter))
				{
					DamagedCharacters.Add(DamagedCharacter);
				}
			}					
			for (auto const& DamagedCharacter : DamagedCharacters)
			{
				DamagedCharacter->LaunchCharacter(Forward * 1000.f, false, false);		

				ANewCharacter* NewCharacter = Cast<ANewCharacter>(DamagedCharacter);
				if (IsValid(NewCharacter))
				{
					NewCharacter->StopMoveWhenAttacked();
				}
			}
		}		
		FColor DrawColor = bIsHitDetected ? FColor::Green : FColor::Red;		
		MulticastRPCDrawDebugSphere(DrawColor, Start, End, Forward);
	}
}

void ANewCharacter::OnDeath()
{
	ANewPlayerController* NewPC = GetController<ANewPlayerController>();
	if (IsValid(NewPC) && HasAuthority())
	{
		NewPC->OnCharacterDead();
		MulticastRPCRespawnCharacter();
	}
	/*if (IsValid(NewPC) && IsLocallyControlled())
	{
		ClientRPCRespawnCharacter();
	}*/
}

void ANewCharacter::ServerRPCAttack_Implementation()
{
	MulticastRPCAttack();
}

void ANewCharacter::MulticastRPCAttack_Implementation()
{	
	if (HasAuthority())
	{
		bCanAttack = false;

		OnRep_CanAttack();

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda
		([&]() -> void
			{void PlayMeleeAttackMontage();
				bCanAttack = true;
				OnRep_CanAttack();
			}), AttackMontagePlayTime, false
		);
	}
	PlayMeleeAttackMontage();
}

void ANewCharacter::MulticastRPCDrawDebugSphere_Implementation(const FColor& DrawColor, FVector TraceStart, FVector TraceEnd, FVector Forward)
{
	const float MeleeAttackRange = 50.f;
	const float MeleeAttackRadius = 50.f;
	FVector CapsuleOrigin = TraceStart + (TraceEnd - TraceStart) * 0.5f;
	float CapsuleHalfHeight = MeleeAttackRange * 0.5f;
	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, MeleeAttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.f);
}

void ANewCharacter::MulticastRPCRespawnCharacter_Implementation()
{	
	SetActorLocation(FVector(0.f, 0.f, 20.f));	
}


void ANewCharacter::OnRep_CanAttack()
{
	if (bCanAttack)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
}

void ANewCharacter::PlayMeleeAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (IsValid(AnimInstance))
	{
		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(AttackMontage);
	}

	//child actor play montage
	const TArray<USceneComponent*> ChildrenArray = GetMesh()->GetAttachChildren();

	for (USceneComponent* Child : ChildrenArray)
	{		
		if (USkeletalMeshComponent* SubMesh = Cast<USkeletalMeshComponent>(Child))
		{
			if (UAnimInstance* AnimInst = SubMesh->GetAnimInstance())
			{
				AnimInst->Montage_Play(AttackMontage);
			}
		}
	}
}

void ANewCharacter::StopMoveWhenAttacked()
{
	GetWorld()->GetTimerManager().SetTimer(StopMoveHandle, this, &ThisClass::CanMoveTimerElapsed, 2.f, false);
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void ANewCharacter::CanMoveTimerElapsed()
{
	GetWorld()->GetTimerManager().ClearTimer(StopMoveHandle);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ANewCharacter::HandleMoveInput(const FInputActionValue& InValue)
{
	if (!IsValid(Controller))
	{
		//UE_LOG(LogTemp, Error, TEXT("Controller is invalid."));
		return;
	}

	const FVector2D InMovementVector = InValue.Get<FVector2D>();

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator ControlYawRotation(0.0f, ControlRotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(ControlYawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(ControlYawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InMovementVector.X);
	AddMovementInput(RightDirection, InMovementVector.Y);
}

void ANewCharacter::HandleLookInput(const FInputActionValue& InValue)
{
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("Controller is invalid."));
		return;
	}

	const FVector2D InLookVector = InValue.Get<FVector2D>();

	AddControllerYawInput(InLookVector.X);
	AddControllerPitchInput(InLookVector.Y);
}

void ANewCharacter::HandleAttackInput(const FInputActionValue& InValue)
{
	if (bCanAttack && !GetCharacterMovement()->IsFalling())
	{
		ServerRPCAttack();
	}
}

