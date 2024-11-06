// Fill out your copyright notice in the Description page of Project Settings.


#include "Room2_Actor_BigPaper.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ARoom2_Actor_BigPaper::ARoom2_Actor_BigPaper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    textRender = nullptr;
}

// Called when the game starts or when spawned
void ARoom2_Actor_BigPaper::BeginPlay()
{
	Super::BeginPlay();
	
    textRender = FindComponentByClass<UTextRenderComponent>();

	if (textRender)
	{
		GenerateRandomNumbersAndDisplay();
	}
}

// Called every frame
void ARoom2_Actor_BigPaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Generate random numbers and display them in the text render
void ARoom2_Actor_BigPaper::GenerateRandomNumbersAndDisplay()
{
    FString DisplayText;

    for (int32 i = 0; i < 4; i++)
    {
        for (int32 j = 0; j < 4; j++)
        {
            // Generate a random number between 0 and 9
            randomNumberArray[i][j] = FMath::RandRange(0, 9);

            DisplayText += FString::FromInt(randomNumberArray[i][j]) + TEXT("\t");
        }
        DisplayText += TEXT("\n");
    }

    textRender->SetText(FText::FromString(DisplayText));
}

void ARoom2_Actor_BigPaper::ResetCode()
{
	GenerateRandomNumbersAndDisplay();
}

FString ARoom2_Actor_BigPaper::GetCorrectCode()
{
	FString correctCode;
	int32 correctCodeArray[4];

    if (bigPaperID == 1) {
        // Correct sequence for Player 1
		correctCodeArray[0] = randomNumberArray[2][3];
		correctCodeArray[1] = randomNumberArray[3][0];
		correctCodeArray[2] = randomNumberArray[2][2];
		correctCodeArray[3] = randomNumberArray[0][1];
	}
	else if (bigPaperID == 2) {
		// Correct sequence for Player 2
		correctCodeArray[0] = randomNumberArray[1][1];
		correctCodeArray[1] = randomNumberArray[3][2];
		correctCodeArray[2] = randomNumberArray[0][3];
		correctCodeArray[3] = randomNumberArray[2][0];
	}

	// Convert the correct sequence to a string
	correctCode = FString::FromInt(correctCodeArray[0]) + FString::FromInt(correctCodeArray[1]) + FString::FromInt(correctCodeArray[2]) + FString::FromInt(correctCodeArray[3]);

	return correctCode;
}