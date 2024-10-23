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
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    // Bind overlap events
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom1_Actor_PressurePlate::OnOverlapBegin);

    // Create and set up the mesh for the pressure plate
    PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateMesh"));
    PressurePlateMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARoom1_Actor_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

    // Get the initial location of the pressure plate
    InitialLocation = PressurePlateMesh->GetComponentLocation();

    // Calculate the target lowered position
    TargetLocation = InitialLocation;
    TargetLocation.Z -= LoweredHeight;
	
}

// Called every frame
void ARoom1_Actor_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // If the plate is lowering, move it down smoothly
    if (bIsLowering)
    {
        FVector CurrentLocation = PressurePlateMesh->GetComponentLocation();
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, LoweringSpeed);
        PressurePlateMesh->SetWorldLocation(NewLocation);

        // Stop lowering when the plate reaches the target
        if (FVector::Dist(CurrentLocation, TargetLocation) <= KINDA_SMALL_NUMBER)
        {
            bIsLowering = false;
        }
    }
}

// Called when the player steps on the plate
void ARoom1_Actor_PressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        bIsLowering = true;  // Start lowering the plate
        bIsRaising = false;  // Stop raising if the plate was going up
        if (TargetDoor)
        {
            TargetDoor->OpenDoor();  // Open the door
        }
    }
}