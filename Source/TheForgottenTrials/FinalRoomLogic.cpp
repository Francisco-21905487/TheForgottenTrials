// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalRoomLogic.h"
#include "Room1_Actor_MazeDoors.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinalRoomLogic::AFinalRoomLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EthanVotes = 0;
	IsabelVotes = 0;
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

void AFinalRoomLogic::RegisterVote(FString VoteFor)
{
    if (VoteFor == "Isabel")
    {
        IsabelVotes++;
    }
    else if (VoteFor == "Ethan")
    {
        EthanVotes++;
    }

    // Check if both votes have been cast
    if (EthanVotes + IsabelVotes == 2)
    {
        DetermineOutcome();
    }
}

void AFinalRoomLogic::DetermineOutcome()
{
    if (EthanVotes == 1 && IsabelVotes == 1)
    {
        if (EthanDoor) EthanDoor->OpenDoor();
        if (IsabelDoor) IsabelDoor->OpenDoor();
        //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Both live!"));
    }
    else if (EthanVotes == 2)
    {
        if (EthanDoor)
        {
            //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Calling OpenDoor() on EthanDoor."));
            EthanDoor->OpenDoor();
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("EthanDoor is null!"));
        }
    }
    else if (IsabelVotes == 2)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Isabel lives!"));
        if (IsabelDoor) IsabelDoor->OpenDoor();
        //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Isabel lives!"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Both die! No doors open."));
    }
}

