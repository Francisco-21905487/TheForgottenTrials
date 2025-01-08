// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerDataTable.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
    GENERATED_BODY()

public:
    // The character class to spawn for this player
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<ACharacter> CharacterClass;

    // The PlayerStart tag to spawn at
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName SpawnTag; 
};