// Fill out your copyright notice in the Description page of Project Settings.


#include "TheForgottenTrial_CheatManager.h"
#include "Room1_Actor_MazeDoors.h"
#include "Room2_Actor_Keypad.h"
#include "Room2_Actor_Bigpaper.h"
#include "Kismet/GameplayStatics.h"

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

/*
//Missing code for CompleteRoom3 and CompleteRoom4
void UTheForgottenTrial_CheatManager::CompleteRoom3()
{

}

void UTheForgottenTrial_CheatManager::CompleteRoom4()
{

}
*/