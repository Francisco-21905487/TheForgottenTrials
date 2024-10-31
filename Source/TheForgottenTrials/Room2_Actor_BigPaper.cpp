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

    TextRender = nullptr;
}

// Called when the game starts or when spawned
void ARoom2_Actor_BigPaper::BeginPlay()
{
	Super::BeginPlay();
	
    TextRender = FindComponentByClass<UTextRenderComponent>();

	if (TextRender)
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
            RandomNumberArray[i][j] = FMath::RandRange(0, 9);

            DisplayText += FString::FromInt(RandomNumberArray[i][j]) + TEXT("\t");
        }
        DisplayText += TEXT("\n");
    }

    TextRender->SetText(FText::FromString(DisplayText));
}

void ARoom2_Actor_BigPaper::ResetCode()
{
	GenerateRandomNumbersAndDisplay();
}

FString ARoom2_Actor_BigPaper::GetCorrectCode()
{
	FString CorrectCode;
	int32 CorrectCodeArray[4];

    if (BigPaperID == 1) {
        // Correct sequence for Player 1
        CorrectCodeArray[0] = RandomNumberArray[2][3];
        CorrectCodeArray[1] = RandomNumberArray[3][0];
        CorrectCodeArray[2] = RandomNumberArray[2][2];
        CorrectCodeArray[3] = RandomNumberArray[0][1];
	}
	else if (BigPaperID == 2) {
		// Correct sequence for Player 2
		CorrectCodeArray[0] = RandomNumberArray[1][1];
		CorrectCodeArray[1] = RandomNumberArray[3][2];
		CorrectCodeArray[2] = RandomNumberArray[0][3];
		CorrectCodeArray[3] = RandomNumberArray[2][0];
	}

	// Convert the correct sequence to a string
	CorrectCode = FString::FromInt(CorrectCodeArray[0]) + FString::FromInt(CorrectCodeArray[1]) + FString::FromInt(CorrectCodeArray[2]) + FString::FromInt(CorrectCodeArray[3]);

	return CorrectCode;
}