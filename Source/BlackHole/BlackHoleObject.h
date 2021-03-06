// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleObject.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class BLACKHOLE_API ABlackHoleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHoleObject();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* StaticMeshcomp;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* InnerSphere;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* OuterSphere;

	UFUNCTION()
	void OverLapInnerSPhere(UPrimitiveComponent* PrimitiveComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
