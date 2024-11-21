// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_FinalDoor.h"

// Sets default values
ARoom1_Actor_FinalDoor::ARoom1_Actor_FinalDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void ARoom1_Actor_FinalDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom1_Actor_FinalDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom1_Actor_FinalDoor::OnInteract() 
{
	UE_LOG(LogTemp, Display, TEXT("Interacted with door"));
}

