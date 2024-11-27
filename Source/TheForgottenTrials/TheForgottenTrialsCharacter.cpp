// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheForgottenTrialsCharacter.h"
#include "TheForgottenTrialsProjectile.h"
#include "Room2_Actor_Keypad.h"
#include "Room1_Actor_Button.h"
#include "Room4_VotingButton.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include <Kismet/GameplayStatics.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheForgottenTrialsCharacter

ATheForgottenTrialsCharacter::ATheForgottenTrialsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ATheForgottenTrialsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	TArray<AActor*> foundCheatManagerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARooms_Actor_CheatManager::StaticClass(), foundCheatManagerActors);

	for (AActor* cheatManagerActor : foundCheatManagerActors)
	{
		actorCheatManager = Cast<ARooms_Actor_CheatManager>(cheatManagerActor);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ATheForgottenTrialsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheForgottenTrialsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheForgottenTrialsCharacter::Look);
		
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATheForgottenTrialsCharacter::Interact);

		//cheats
		EnhancedInputComponent->BindAction(Cheat1Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat1);
		EnhancedInputComponent->BindAction(Cheat2Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat2);
		EnhancedInputComponent->BindAction(Cheat3Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat3);
		EnhancedInputComponent->BindAction(Cheat4Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat4);
        EnhancedInputComponent->BindAction(Cheat5Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat5);
		EnhancedInputComponent->BindAction(Cheat6Action, ETriggerEvent::Started, this, &ATheForgottenTrialsCharacter::ActivateCheat6);


	}
}


void ATheForgottenTrialsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATheForgottenTrialsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheForgottenTrialsCharacter::Interact()
{
	// Perform a line trace or overlap check to find the keypad actor
	FHitResult HitResult;
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 200.0f); // Adjust the range as needed

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		IInteractable* InteractableActor = Cast<IInteractable>(HitResult.GetActor());
		if (InteractableActor)
		{
			InteractableActor->Interact();
		}
	}
}

//cheats Functions

void ATheForgottenTrialsCharacter::ActivateCheat1()
{
	actorCheatManager->CompleteRoom1();
}

void ATheForgottenTrialsCharacter::ActivateCheat2()
{
	actorCheatManager->CompleteRoom2();
}

void ATheForgottenTrialsCharacter::ActivateCheat3()
{
	actorCheatManager->CompleteRoom3();
}

void ATheForgottenTrialsCharacter::ActivateCheat4()
{
	actorCheatManager->ShowCodeRoom2();
}

void ATheForgottenTrialsCharacter::ActivateCheat5()
{
	actorCheatManager->TeleportToNextWaypoint();
}

void ATheForgottenTrialsCharacter::ActivateCheat6()
{
	actorCheatManager->TeleportToPreviousWaypoint();
}