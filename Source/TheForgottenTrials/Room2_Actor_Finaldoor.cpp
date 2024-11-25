// Fill out your copyright notice in the Description page of Project Settings.


#include "Room2_Actor_Finaldoor.h"

// Sets default values
ARoom2_Actor_Finaldoor::ARoom2_Actor_Finaldoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = doorMesh;

	targetZPosition = 0.0f;
	moveSpeed = 100.0f;
	opening = false;
}

// Called when the game starts or when spawned
void ARoom2_Actor_Finaldoor::BeginPlay()
{
	Super::BeginPlay();

	initialPosition = GetActorLocation();
	
}

// Called every frame
void ARoom2_Actor_Finaldoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
    
    FVector currentLocation = GetActorLocation();

    if (opening)
    {
        // Smoothly move the door down towards the target Z position
        currentLocation.Z = FMath::FInterpTo(currentLocation.Z, targetZPosition, DeltaTime, moveSpeed);
        SetActorLocation(currentLocation);

        // Stop opening when we reach the target position
        if (FMath::IsNearlyEqual(currentLocation.Z, targetZPosition, 1.0f))
        {
            opening = false;
        }
    }

}

void ARoom2_Actor_Finaldoor::OpenDoor()
{
    opening = true;
}