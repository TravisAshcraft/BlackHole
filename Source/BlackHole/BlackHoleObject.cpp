// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleObject.h"
#include "Components/SphereComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
ABlackHoleObject::ABlackHoleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets the Static mesh as the default root component
	StaticMeshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshcomp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StaticMeshcomp;

	//Creates innersphere
	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphere->SetSphereRadius(100);
	InnerSphere->SetupAttachment(StaticMeshcomp);

	//Binds the function to the event 
	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHoleObject::OverLapInnerSPhere);

	//Creates outersphere
	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphere->SetSphereRadius(3000);
	OuterSphere->SetupAttachment(StaticMeshcomp);
}

// Called when the game starts or when spawned
void ABlackHoleObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHoleObject::OverLapInnerSPhere(UPrimitiveComponent* PrimitiveComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, INT32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}


// Called every frame
void ABlackHoleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphere->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			//The Component we are looking for! It needs to be simulating physics!

			const float SphereRadius = OuterSphere->GetScaledSphereRadius();
			const float ForceStrength = -2000; //Negative so it pulls instead of pushes

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}


