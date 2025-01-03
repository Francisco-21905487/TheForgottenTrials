// Fill out your copyright notice in the Description page of Project Settings.

#include "Room2_Actor_Keypad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "string"
#include "TheForgottenTrialsPlayerController.h"

// Sets default values
ARoom2_Actor_Keypad::ARoom2_Actor_Keypad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the ProximityBox
	proximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	proximityBox->SetupAttachment(RootComponent);
	proximityBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	proximityBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom2_Actor_Keypad::OnOverlapBegin);
	proximityBox->OnComponentEndOverlap.AddDynamic(this, &ARoom2_Actor_Keypad::OnOverlapEnd);

	// Initialize the KeypadMesh
	keypadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeypadMesh"));
	keypadMesh->SetupAttachment(RootComponent);

	playerInRange = false;
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

void ARoom2_Actor_Keypad::ServerInteract_Implementation(APlayerController* InteractingController)
{
	if (InteractingController)
	{
		ATheForgottenTrialsPlayerController* myPlayerController = Cast<ATheForgottenTrialsPlayerController>(InteractingController);
		if (myPlayerController)
		{
			myPlayerController->ClientOpenKeypadUI(keypadWidgetClass);
		}
	}
}

void ARoom2_Actor_Keypad::Interact()
{
	ServerInteract(interactController);
}


bool ARoom2_Actor_Keypad::CheckCode(FString KeypadCode)
{
	FString CorrectCode = targetBigPaper->GetCorrectCode();

	// Compare the keypad code with the correct code
	if (KeypadCode == CorrectCode)
	{
		targetFinalDoor->OpenDoor();
		return true;
	}
	else
	{
		targetBigPaper->ResetCode();
		return false;
	}
}

void ARoom2_Actor_Keypad::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		AController* playerController = OtherActor->GetInstigatorController();
		if (!playerController) return;

		APlayerController* overlappingPlayerController = Cast<APlayerController>(playerController);
		ACharacter* overlappingCharacter = Cast<ACharacter>(OtherActor);

		interactController = overlappingPlayerController;
		interactCharacter = overlappingCharacter;
		playerInRange = true;
	}
}

void ARoom2_Actor_Keypad::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		playerInRange = false;
		interactController = nullptr;
		interactCharacter = nullptr;
	}
}