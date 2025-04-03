#include "MapObjects/FRBreakableObject.h"
#include "Components/SphereComponent.h"

AFRBreakableObject::AFRBreakableObject()
	:HitCountToBreakeObj(3),
	CurrentHitCount(0)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComp->SetupAttachment(RootComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComp->SetupAttachment(RootComp);
}

void AFRBreakableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFRBreakableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFRBreakableObject::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvnet, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}



