// Fill out your copyright notice in the Description page of Project Settings.

#include "Room2_Actor_Keypad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"
#include "string"

// Sets default values
ARoom2_Actor_Keypad::ARoom2_Actor_Keypad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the ProximityBox
	ProximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	ProximityBox->SetupAttachment(RootComponent);
	ProximityBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	ProximityBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom2_Actor_Keypad::OnOverlapBegin);
	ProximityBox->OnComponentEndOverlap.AddDynamic(this, &ARoom2_Actor_Keypad::OnOverlapEnd);

	// Initialize the KeypadMesh
	KeypadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeypadMesh"));
	KeypadMesh->SetupAttachment(RootComponent);

	PlayerInRange = false;
}

// Called when the game starts or when spawned
void ARoom2_Actor_Keypad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoom2_Actor_Keypad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom2_Actor_Keypad::Interact()
{
	if (PlayerInRange)
	{
		// Get the player controller
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController && KeypadWidgetClass)
		{
			// Create the widget
			KeypadWidget = CreateWidget<UUserWidget>(PlayerController, KeypadWidgetClass);
			if (KeypadWidget)
			{
				// Add the widget to the viewport
				KeypadWidget->AddToViewport();

				// Set input mode to game and UI
				FInputModeGameAndUI InputMode;
				InputMode.SetWidgetToFocus(KeypadWidget->TakeWidget());
				PlayerController->SetInputMode(InputMode);

				// Show the mouse cursor
				PlayerController->bShowMouseCursor = true;

				// Disable input for the player character
				ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				if (PlayerCharacter)
				{
					PlayerCharacter->DisableInput(PlayerController);
				}
			}
		}
	}
}

void ARoom2_Actor_Keypad::CloseWidget()
{
	// Remove the widget from the viewport
	if (KeypadWidget)
	{
		KeypadWidget->RemoveFromViewport();
		KeypadWidget = nullptr;
	}

	// Get the player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// Set input mode back to game only
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		// Hide the mouse cursor
		PlayerController->bShowMouseCursor = false;

		// Re-enable input for the player character
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			PlayerCharacter->EnableInput(PlayerController);
		}
	}
}

bool ARoom2_Actor_Keypad::CheckCode(FString KeypadCode)
{
	FString CorrectCode = TargetBigPaper->GetCorrectCode();

	// Compare the keypad code with the correct code
	if (KeypadCode == CorrectCode)
	{
		TargetFinalDoor->OpenDoor();
		return true;
	}
	else
	{
		TargetBigPaper->ResetCode();
		return false;
	}
}

void ARoom2_Actor_Keypad::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		PlayerInRange = true;
	}
}

void ARoom2_Actor_Keypad::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		PlayerInRange = false;
	}
}