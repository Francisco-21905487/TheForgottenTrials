// Fill out your copyright notice in the Description page of Project Settings.


#include "Rooms_Actor_CheatManager.h"
#include "Room1_Actor_MazeDoors.h"
#include "Room2_Actor_Keypad.h"
#include "Room2_Actor_Bigpaper.h"
#include "Room3_Actor_DoorsManager.h"
#include "Room3_Actor_SymbolsManager.h"
#include "TeleportsManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

// Sets default values
ARooms_Actor_CheatManager::ARooms_Actor_CheatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentWaypoint = 0;

}

// Called when the game starts or when spawned
void ARooms_Actor_CheatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARooms_Actor_CheatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Functions to handle the completion of the rooms.
void ARooms_Actor_CheatManager::CompleteRoom1()
{
	TArray<AActor*> foundMazeDoorsActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom1_Actor_MazeDoors::StaticClass(), foundMazeDoorsActors);

	for (AActor* actor : foundMazeDoorsActors)
	{
		ARoom1_Actor_MazeDoors* mazeDoorsActor = Cast<ARoom1_Actor_MazeDoors>(actor);
		mazeDoorsActor->OpenDoor();
	}
}

void ARooms_Actor_CheatManager::CompleteRoom2()
{
	TArray<AActor*> foundKeypadActors;
	TArray<AActor*> foundBigpaperActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom2_Actor_Keypad::StaticClass(), foundKeypadActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom2_Actor_BigPaper::StaticClass(), foundBigpaperActors);

	for (AActor* bigPaperActor : foundBigpaperActors)
	{
		for (AActor* keypadActor : foundKeypadActors)
		{
			ARoom2_Actor_BigPaper* bigpaperActorClass = Cast<ARoom2_Actor_BigPaper>(bigPaperActor);
			ARoom2_Actor_Keypad* keypadActorClass = Cast<ARoom2_Actor_Keypad>(keypadActor);

			FString correctCodeBigPaper = bigpaperActorClass->GetCorrectCode();
			keypadActorClass->CheckCode(correctCodeBigPaper);
		}
	}
}

void ARooms_Actor_CheatManager::ShowCodeRoom2()
{
	TArray<AActor*> foundBigpaperActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom2_Actor_BigPaper::StaticClass(), foundBigpaperActors);

	for (AActor* bigPaperActor : foundBigpaperActors)
	{
		ARoom2_Actor_BigPaper* bigpaperActorClass = Cast<ARoom2_Actor_BigPaper>(bigPaperActor);
		FString correctCodeBigPaper = bigpaperActorClass->GetCorrectCode();

		int32 codeInt = FCString::Atoi(*correctCodeBigPaper);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("The code is: %d"), codeInt));
	}
}

void ARooms_Actor_CheatManager::CompleteRoom3()
{
	TArray<AActor*> foundDoorsManagerActors;
	TArray<AActor*> foundSymbolsManagerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom3_Actor_DoorsManager::StaticClass(), foundDoorsManagerActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom3_Actor_SymbolsManager::StaticClass(), foundSymbolsManagerActors);

	for (AActor* doorManagerActor : foundDoorsManagerActors)
	{
		for (AActor* symbolManagerActor : foundSymbolsManagerActors)
		{
			ARoom3_Actor_DoorsManager* doorsManagerActor = Cast<ARoom3_Actor_DoorsManager>(doorManagerActor);
			ARoom3_Actor_SymbolsManager* symbolsManagerActor = Cast<ARoom3_Actor_SymbolsManager>(symbolManagerActor);

			//Open the door using the interact function to check if the door is correct.
			for (int i = 0; i < 4; i++)
			{
				doorsManagerActor->correctDoors[i]->Interact();
			}

			symbolsManagerActor->finalDoor->OpenDoor();
		}
	}
}

void ARooms_Actor_CheatManager::TeleportToWaypoint(int id)
{
	TArray<AActor*> foundTeleportsManagerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATeleportsManager::StaticClass(), foundTeleportsManagerActors);

	for (AActor* teleportManagerActor : foundTeleportsManagerActors)
	{
		ATeleportsManager* teleportsManagerActor = Cast<ATeleportsManager>(teleportManagerActor);

		//Reset the player to the beginning of the room3
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController && playerController->GetPawn())
		{
			playerController->GetPawn()->SetActorLocation(teleportsManagerActor->teleports[id]->GetActorLocation());
		}
	}
}

void ARooms_Actor_CheatManager::TeleportToNextWaypoint() 
{
	TArray<AActor*> foundTeleportsManagerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATeleportsManager::StaticClass(), foundTeleportsManagerActors);

	for (AActor* teleportManagerActor : foundTeleportsManagerActors)
	{
		ATeleportsManager* teleportsManagerActor = Cast<ATeleportsManager>(teleportManagerActor);

		//Reset the player to the beginning of the room3
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController && playerController->GetPawn())
		{
			currentWaypoint = (currentWaypoint + 1) % (sizeof(teleportsManagerActor->teleports) / sizeof(teleportsManagerActor->teleports[0]));
			playerController->GetPawn()->SetActorLocation(teleportsManagerActor->teleports[currentWaypoint]->GetActorLocation());
		}
	}

}

void ARooms_Actor_CheatManager::TeleportToPreviousWaypoint()
{
	TArray<AActor*> foundTeleportsManagerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATeleportsManager::StaticClass(), foundTeleportsManagerActors);

	for (AActor* teleportManagerActor : foundTeleportsManagerActors)
	{
		ATeleportsManager* teleportsManagerActor = Cast<ATeleportsManager>(teleportManagerActor);

		//Reset the player to the beginning of the room3
		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (playerController && playerController->GetPawn())
        {
            // Calculate the previous waypoint index
            int32 numWaypoints = (sizeof(teleportsManagerActor->teleports) / sizeof(teleportsManagerActor->teleports[0]));
            currentWaypoint = (currentWaypoint - 1 + numWaypoints) % numWaypoints;

            // Teleport the player to the previous waypoint
            playerController->GetPawn()->SetActorLocation(teleportsManagerActor->teleports[currentWaypoint]->GetActorLocation());
        }
	}
}