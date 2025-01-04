// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheForgottenTrialsGameMode.h"
#include "TheForgottenTrialsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"

ATheForgottenTrialsGameMode::ATheForgottenTrialsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
}

APawn* ATheForgottenTrialsGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    APlayerController* PC = Cast<APlayerController>(NewPlayer);
    if (!PC || !StartSpot)
    {
        return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
    }

    // Retrieve the cached row
    if (FPlayerData* CachedRow = PlayerControllerData.Find(PC))
    {
        if (CachedRow->CharacterClass)
        {
            // Spawn with the PawnClass from the cached row
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = NewPlayer;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            FTransform SpawnTransform = StartSpot->GetActorTransform();

            APawn* NewPawn = GetWorld()->SpawnActor<APawn>(
                CachedRow->CharacterClass,
                SpawnTransform,
                SpawnParams
            );

            if (NewPawn)
            {
                return NewPawn;
            }
        }
    }

    // If no cached data or no PawnClass found, fallback:
    return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}

AActor* ATheForgottenTrialsGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    APlayerController* PC = Cast<APlayerController>(Player);
    if (!PC)
    {
        return Super::ChoosePlayerStart_Implementation(Player);
    }

    int32 PlayerIndex = GetNumPlayers() - 1;
    if (PC->GetLocalPlayer())
    {
        PlayerIndex = PC->GetLocalPlayer()->GetControllerId();
    }

    if (PlayerDataTable)
    {
        static const FString ContextString(TEXT("PlayerDataLookup"));
        FName RowName = FName(*FString::FromInt(PlayerIndex));
        FPlayerData* FoundRow = PlayerDataTable->FindRow<FPlayerData>(RowName, ContextString);

        if (FoundRow)
        {
            PlayerControllerData.Add(PC, *FoundRow);
            for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
            {
                APlayerStart* Start = *It;
                if (Start && Start->PlayerStartTag == FoundRow->SpawnTag)
                {
                    return Start;
                }
            }
        }
    }

    // Fallback
    return Super::ChoosePlayerStart_Implementation(Player);
}