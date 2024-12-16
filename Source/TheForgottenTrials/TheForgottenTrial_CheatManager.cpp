// Fill out your copyright notice in the Description page of Project Settings.


#include "TheForgottenTrial_CheatManager.h"
#include "Room1_Actor_MazeDoors.h"
#include "Room2_Actor_Keypad.h"
#include "Room2_Actor_Bigpaper.h"
#include "Room3_Actor_DoorsManager.h"
#include "Room3_Actor_SymbolsManager.h"
#include "TeleportsManager.h"
#include "Kismet/GameplayStatics.h"

//Functions to handle the completion of the rooms.
void UTheForgottenTrial_CheatManager::CompleteRoom1()
{
	TArray<AActor*> foundMazeDoorsActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoom1_Actor_MazeDoors::StaticClass(), foundMazeDoorsActors);

	for (AActor* actor : foundMazeDoorsActors)
	{
		ARoom1_Actor_MazeDoors* mazeDoorsActor = Cast<ARoom1_Actor_MazeDoors>(actor);
		mazeDoorsActor->OpenDoor();
	}
}

void UTheForgottenTrial_CheatManager::CompleteRoom2()
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

void UTheForgottenTrial_CheatManager::ShowCodeRoom2() 
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

void UTheForgottenTrial_CheatManager::CompleteRoom3()
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

void UTheForgottenTrial_CheatManager::TeleportToWaypoint(int id)
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