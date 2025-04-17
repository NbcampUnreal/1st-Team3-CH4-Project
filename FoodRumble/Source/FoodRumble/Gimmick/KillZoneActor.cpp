#include "Gimmick/KillZoneActor.h"

#include "Character/NewCharacter.h"

#include "Components/BoxComponent.h"

AKillZoneActor::AKillZoneActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComp->SetupAttachment(CollisionComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZoneActor::OnOverlap);
}

void AKillZoneActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		ANewCharacter* NewCharacter = Cast<ANewCharacter>(OtherActor);
		if (IsValid(NewCharacter) && HasAuthority())
		{
			NewCharacter->OnDeath();			
			//UE_LOG(LogTemp, Warning, TEXT("Player Death"));
		}
	}
}


