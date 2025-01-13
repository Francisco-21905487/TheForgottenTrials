// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheForgottenTrialsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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

void ATheForgottenTrialsPlayerController::ClientOpenUI_Implementation(TSubclassOf<UUserWidget> widgetClass)
{
    if (IsLocalController() && widgetClass)
    {
        UUserWidget* widget = CreateWidget<UUserWidget>(this, widgetClass);
        if (widget)
        {
            widget->AddToViewport();

            // Set input mode
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(widget->TakeWidget());
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

void ATheForgottenTrialsPlayerController::OpenPauseUI(TSubclassOf<UUserWidget> pauseWidgetClass)
{
    if (IsLocalController() && pauseWidgetClass)
    {
        UUserWidget* pauseWidget = CreateWidget<UUserWidget>(this, pauseWidgetClass);
        if (pauseWidget)
        {
            pauseWidget->AddToViewport();

            // Set input mode
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(pauseWidget->TakeWidget());
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

void ATheForgottenTrialsPlayerController::ClientOpenWinMenu_Implementation(FName winmenu)
{
    if (IsLocalController())
    {
        UGameplayStatics::OpenLevel(this, winmenu);
    }
}

void ATheForgottenTrialsPlayerController::ClientPlaySounds_Implementation(UObject* WorldObject, USoundBase* sound, float volume, float pitch, float startTime)
{
    if (IsLocalController() && sound)
    {
        UGameplayStatics::PlaySound2D(WorldObject, sound, volume, pitch, startTime);
    }
}