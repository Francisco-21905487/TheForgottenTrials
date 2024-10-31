// Fill out your copyright notice in the Description page of Project Settings.


#include "Room2_Actor_Finaldoor.h"

// Sets default values
ARoom2_Actor_Finaldoor::ARoom2_Actor_Finaldoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	TargetZPosition = 0.0f;
	MoveSpeed = 100.0f;
	Opening = false;
}

// Called when the game starts or when spawned
void ARoom2_Actor_Finaldoor::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetActorLocation();
	
}

// Called every frame
void ARoom2_Actor_Finaldoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
    
    FVector CurrentLocation = GetActorLocation();

    if (Opening)
    {
        // Smoothly move the door down towards the target Z position
        CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, TargetZPosition, DeltaTime, MoveSpeed);
        SetActorLocation(CurrentLocation);

        // Stop opening when we reach the target position
        if (FMath::IsNearlyEqual(CurrentLocation.Z, TargetZPosition, 1.0f))
        {
            Opening = false;
        }
    }

}

void ARoom2_Actor_Finaldoor::OpenDoor()
{
    Opening = true;
}