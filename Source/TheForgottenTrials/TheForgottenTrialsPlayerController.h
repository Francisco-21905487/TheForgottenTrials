// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheForgottenTrialsPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class THEFORGOTTENTRIALS_API ATheForgottenTrialsPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		UFUNCTION(Client, Reliable)
		void ClientOpenUI(TSubclassOf<UUserWidget> widgetClass);
		
		UFUNCTION(BlueprintCallable)
		void OpenPauseUI(TSubclassOf<UUserWidget> pauseWidgetClass);

		UFUNCTION(Client, Reliable)
		void ClientResetRoom3(FVector waypointStartRoom3);

		UFUNCTION(Client, Reliable)
		void ClientOpenWinMenu(FName winmenu);

		UFUNCTION(Client, Reliable)
		void ClientPlaySounds(UObject* WorldObject, USoundBase* sound, float volume, float pitch, float startTime);
	
	protected:
		virtual void BeginPlay() override;

		/** Input Mapping Context to be used for player input */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputMappingContext* InputMappingContext;
};
