// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_MazeDoors.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoom1_Actor_MazeDoors::ARoom1_Actor_MazeDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

    TargetZPosition = 0.0f;
    MoveSpeed = 100.0f;
    bIsOpening = false;

}

// Called when the game starts or when spawned
void ARoom1_Actor_MazeDoors::BeginPlay()
{
	Super::BeginPlay();

    InitialPosition = GetActorLocation();
}

// Called every frame
void ARoom1_Actor_MazeDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();

    if (bIsOpening)
    {
        // Smoothly move the door down towards the target Z position
        CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, TargetZPosition, DeltaTime, MoveSpeed);
        SetActorLocation(CurrentLocation);

        // Stop opening when we reach the target position
        if (FMath::IsNearlyEqual(CurrentLocation.Z, TargetZPosition, 1.0f))
        {
            bIsOpening = false;
        }
    }
}

void ARoom1_Actor_MazeDoors::OpenDoor()
{
    bIsOpening = true;
}