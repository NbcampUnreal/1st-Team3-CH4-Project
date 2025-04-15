#include "Character/NewCharacter.h"

#include "Item/HJItem.h"
#include "Item/FoodCoinItem/FoodCoinItem.h"
#include "Character/NewPlayerState.h"
#include "Item/FoodCoinItem/PlayerCoinComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"

ANewCharacter::ANewCharacter()
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
}

void ANewCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, FaceIndex);
	DOREPLIFETIME(ThisClass, ShirtsIndex);
	DOREPLIFETIME(ThisClass, PantsIndex);
	DOREPLIFETIME(ThisClass, AccessoryIndex);
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
}

void ANewCharacter::ServerRPCSetRandomCostume_Implementation()
{
	FaceIndex = RandomFace.IsEmpty() ? -1 : FMath::RandRange(0, RandomFace.Num() - 1);
	ShirtsIndex = RandomShirts.IsEmpty() ? -1 : FMath::RandRange(0, RandomShirts.Num() - 1);
	PantsIndex = RandomPants.IsEmpty() ? -1 : FMath::RandRange(0, RandomPants.Num() - 1);
	AccessoryIndex = RandomAccessory.IsEmpty() ? -1 : FMath::RandRange(0, RandomAccessory.Num() - 1);

	ApplyCostume();
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

