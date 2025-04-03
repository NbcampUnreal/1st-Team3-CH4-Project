

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DonutActor.generated.h"

UCLASS()
class FOODRUMBLE_API ADonutActor : public AActor
{
	GENERATED_BODY()
	
public:
    ADonutActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UFUNCTION()
    void StartRolling();

    UFUNCTION()
    void DestroyDonut();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> DonutMesh;

    FTimerHandle RollTimerHandle;
    FTimerHandle DestroyTimerHandle;

    bool bShouldMove;

    UPROPERTY(EditAnywhere, Category = "Donut Settings", meta = (ClampMin = "0.0"))
    float DelayTime;

    UPROPERTY(EditAnywhere, Category = "Donut Settings", meta = (ClampMin = "0.0"))
    float RollForce;

};