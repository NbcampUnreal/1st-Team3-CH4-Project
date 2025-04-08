#include "Item/BaseItem.h"
#include "GameFramework/Character.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = MeshComponent;
	//for overlap collision
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(60.f);
	CollisionSphere->SetupAttachment(RootComponent);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionSphere)
	{
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlap);
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
