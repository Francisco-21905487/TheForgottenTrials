// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheForgottenTrialsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"

void ATheForgottenTrialsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ATheForgottenTrialsPlayerController::ClientOpenKeypadUI_Implementation(TSubclassOf<UUserWidget> keypadWidgetClass)
{
    if (IsLocalController() && keypadWidgetClass)
    {
        UUserWidget* keypadWidget = CreateWidget<UUserWidget>(this, keypadWidgetClass);
        if (keypadWidget)
        {
            keypadWidget->AddToViewport();

            // Set input mode
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(keypadWidget->TakeWidget());
            SetInputMode(InputMode);
            bShowMouseCursor = true;

            APawn* currentPawn = GetPawn();
            if (currentPawn)
            {
                currentPawn->DisableInput(this);
            }
        }
    }
}

void ATheForgottenTrialsPlayerController::ClientResetRoom3_Implementation(FVector waypointStartRoom3)
{
    if (IsLocalController())
    {
        this->GetPawn()->SetActorLocation(waypointStartRoom3);
    }
}

