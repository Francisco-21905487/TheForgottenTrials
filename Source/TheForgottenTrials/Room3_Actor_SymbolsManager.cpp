// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_SymbolsManager.h"
#include "Room3_Actor_DoorsManager.h"

// Sets default values
ARoom3_Actor_SymbolsManager::ARoom3_Actor_SymbolsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoom3_Actor_SymbolsManager::BeginPlay()
{
	Super::BeginPlay();

	//SetCorrectSymbols();
}

// Called every frame
void ARoom3_Actor_SymbolsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom3_Actor_SymbolsManager::SetCorrectSymbols()
{
    correctSymbolSequence.Empty();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (doorsManager->correctDoors[i]->symbolActor->GetName() == symbols[j]->GetName())
            {
                symbols[j]->correctSymbol = true;
                correctSymbolSequence.Add(symbols[j]);
				break;
			}
        }
    }
}

void ARoom3_Actor_SymbolsManager::CheckSequenceOfSymbols(ARoom3_Actor_Symbols* interactedSymbol)
{
	if (currentSequenceIndex < correctSymbolSequence.Num() && correctSymbolSequence[currentSequenceIndex] == interactedSymbol)
	{
		currentSequenceIndex++;

		if (currentSequenceIndex == correctSymbolSequence.Num())
		{
			finalDoor->OpenDoor();
		}
	}
	else
	{
		if (currentSequenceIndex > 0)
		{
			for (int i = 0; i < currentSequenceIndex; i++)
			{
				correctSymbolSequence[i]->resetMovement = true;
			}
		}

		interactedSymbol->resetMovement = true;
		currentSequenceIndex = 0;
		//If we want to add some user feedback put it here
	}
}