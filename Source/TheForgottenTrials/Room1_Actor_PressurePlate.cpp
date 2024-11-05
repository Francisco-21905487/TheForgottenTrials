// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Room1_Actor_MazeDoors.h" 

// Sets default values
ARoom1_Actor_PressurePlate::ARoom1_Actor_PressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and set up the trigger box
    triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = triggerBox;
    triggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    triggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    triggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    triggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    // Bind overlap events
    triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom1_Actor_PressurePlate::OnOverlapBegin);

    // Create and set up the mesh for the pressure plate
    pressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateMesh"));
    pressurePlateMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARoom1_Actor_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

    // Get the initial location of the pressure plate
    initialLocation = pressurePlateMesh->GetComponentLocation();

    // Calculate the target lowered position
    targetLocation = initialLocation;
    targetLocation.Z -= loweredHeight;
	
}

// Called every frame
void ARoom1_Actor_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // If the plate is lowering, move it down smoothly
    if (lowering)
    {
        FVector CurrentLocation = pressurePlateMesh->GetComponentLocation();
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, targetLocation, DeltaTime, loweringSpeed);
        pressurePlateMesh->SetWorldLocation(NewLocation);

        // Stop lowering when the plate reaches the target
        if (FVector::Dist(CurrentLocation, targetLocation) <= KINDA_SMALL_NUMBER)
        {
            lowering = false;
        }
    }
}

// Called when the player steps on the plate
void ARoom1_Actor_PressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        lowering = true;  // Start lowering the plate
        if (targetDoor)
        {
            targetDoor->OpenDoor();  // Open the door
        }
    }
}