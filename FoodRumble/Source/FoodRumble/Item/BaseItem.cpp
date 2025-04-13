#include "Item/BaseItem.h"
#include "GameFramework/Character.h"

ABaseItem::ABaseItem()
{
	bReplicates = true;
	SetReplicates(true);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;
	RootComponent->SetWorldScale3D(FVector(0.7f));
	
	/*MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	MeshComponent->BodyInstance.bUseCCD = true;*/

	//for overlap collision
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(60.f);
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetWorldScale3D(FVector(1.4f));
	//CollisionSphere->SetRelativeLocation(FVector(0.f, 0.f, 42.f));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetRelativeLocation(FVector(0.f, 0.f, -42.f));

	BubbleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleMesh"));
	BubbleMesh->SetupAttachment(RootComponent);
	BubbleMesh->SetWorldScale3D(FVector(1.3f));
	//BubbleMesh->SetRelativeLocation(FVector(0.f, 0.f, 42.f));


	//BubbleMesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMesh.Succeeded())
	{
		BubbleMesh->SetStaticMesh(SphereMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BubbleMat(TEXT("/Game/YJ_Item/FX/sA_PickupSet_1/BubbleEffect/M_Bubble"));
	if (BubbleMat.Succeeded())
	{
		BubbleMesh->SetMaterial(0, BubbleMat.Object);
	}
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseItem::StopPhysics, 5.0f, false);
	if (CollisionSphere)
	{
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlap);
	}
}
void ABaseItem::StopPhysics()
{
	if (MeshComponent)
	{
		MeshComponent->SetSimulatePhysics(false);
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}


void ABaseItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//when overlap + character -> activateItem, destroyitem
	if (OtherActor && OtherActor != this)
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
		if (PlayerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("[baseItem]player overlapped"));
			CachedActor = OtherActor;
			ActivateItem(PlayerCharacter);
			DestroyItem();
		}
		
	}
}


void ABaseItem::ActivateItem_Implementation(AActor* TargetActor)
{

}

void ABaseItem::DestroyItem()
{
	Destroy();
}


//void ABaseItem::Multicast_PlaySpawnEffect()
//{
//
//}
