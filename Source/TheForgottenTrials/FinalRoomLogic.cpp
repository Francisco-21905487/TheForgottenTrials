// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalRoomLogic.h"
#include "Room1_Actor_MazeDoors.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinalRoomLogic::AFinalRoomLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    EthanVote = "";
    IsabelVote = "";
    EthanDoor = nullptr;
    IsabelDoor = nullptr;
}

// Called when the game starts or when spawned
void AFinalRoomLogic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalRoomLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinalRoomLogic::RegisterVote(FString Character, FString VoteFor)
{
    if (Character == "Ethan_C_0")
    {
        EthanVote = VoteFor;
    }
    else if (Character == "Isabel_C_0")
    {
        IsabelVote = VoteFor;
    }

    // Check if both votes have been cast
    if (!EthanVote.IsEmpty() && !IsabelVote.IsEmpty())
    {
        DetermineOutcome();
    }
}

void AFinalRoomLogic::DetermineOutcome()
{
    if (EthanVote == "Ethan" && IsabelVote == "Isabel")
    {
        // Neither door opens
		//Open the lose menu for both players here
    }
    else if (EthanVote == "Isabel" && IsabelVote == "Ethan")
    {
        // Both doors open
        if (EthanDoor) EthanDoor->OpenDoor();
        if (IsabelDoor) IsabelDoor->OpenDoor();
    }
    else if (EthanVote == "Ethan" && IsabelVote == "Ethan")
    {
        // Ethan's door opens
        if (EthanDoor) EthanDoor->OpenDoor();

        //Open the lose menu for Isabel player here
    }
    else if (EthanVote == "Isabel" && IsabelVote == "Isabel")
    {
        // Isabel's door opens
        if (IsabelDoor) IsabelDoor->OpenDoor();

        //Open the lose menu for Ethan player here
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Unexpected vote combination."));
    }
}

