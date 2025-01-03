// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerDataTable.h"
#include "TheForgottenTrialsGameMode.generated.h"

UCLASS(minimalapi)
class ATheForgottenTrialsGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
		ATheForgottenTrialsGameMode();

    protected:
        virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
        virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

        // Reference to your DataTable
        UPROPERTY(EditDefaultsOnly, Category = "Setup")
        UDataTable* PlayerDataTable;

    private:
        UPROPERTY()
        TMap<APlayerController*, FPlayerData> PlayerControllerData;
};