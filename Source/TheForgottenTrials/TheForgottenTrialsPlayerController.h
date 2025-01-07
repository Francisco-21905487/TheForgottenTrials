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
		void ClientOpenKeypadUI(TSubclassOf<UUserWidget> keypadWidgetClass);

		UFUNCTION(Client, Reliable)
		void ClientResetRoom3(FVector waypointStartRoom3);
	
	protected:
		virtual void BeginPlay() override;

		/** Input Mapping Context to be used for player input */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UInputMappingContext* InputMappingContext;
};
