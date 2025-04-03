#include "DonutActor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

ADonutActor::ADonutActor()
    : DelayTime(3.0f)
    , RollForce(500000.0f)
    , bShouldMove(false)
{
    PrimaryActorTick.bCanEverTick = true;

    DonutMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DonutMesh"));
    RootComponent = DonutMesh;

    DonutMesh->SetSimulatePhysics(true);
    DonutMesh->SetEnableGravity(true);
    DonutMesh->SetNotifyRigidBodyCollision(true);
}

void ADonutActor::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(RollTimerHandle, this, &ADonutActor::StartRolling, DelayTime, false);

    DonutMesh->OnComponentHit.AddDynamic(this, &ADonutActor::OnHit);
}

void ADonutActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bShouldMove)
    {
        const FVector Forward = GetActorForwardVector();
        DonutMesh->AddForce(Forward * RollForce);
    }
}

void ADonutActor::StartRolling()
{
    bShouldMove = true;
    
}

void ADonutActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    if (OtherActor->ActorHasTag(TEXT("ElectricWire")))
    {
        OtherActor->Destroy();

        GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ADonutActor::DestroyDonut, 3.0f, false);
    }

}

void ADonutActor::DestroyDonut()
{
    Destroy();
}
