// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWinTrigger::AWinTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Initialize the trigger box
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    // Set up the trigger box collision properties
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Bind overlap event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWinTrigger::OnOverlapBegin);

    // Default win menu level name
    winmenu = "WinMenu";  // Replace with the actual name of your win menu level

}

// Called when the game starts or when spawned
void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
    {
        // Load the win menu level
        UGameplayStatics::OpenLevel(this, winmenu);
    }
}

// Called every frame
void AWinTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

