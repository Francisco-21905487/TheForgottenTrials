// Fill out your copyright notice in the Description page of Project Settings.


#include "Room3_Actor_Symbols.h"
#include "Room3_Actor_SymbolsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TheForgottenTrialsPlayerController.h"

// Sets default values
ARoom3_Actor_Symbols::ARoom3_Actor_Symbols()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the ProximityBox
	proximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	proximityBox->SetupAttachment(RootComponent);
	proximityBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	proximityBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom3_Actor_Symbols::OnOverlapBegin);

	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ARoom3_Actor_Symbols::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom3_Actor_Symbols::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (moving && !resetMovement)
	{
		Multicast_MoveActorPosition(DeltaTime, targetXPosition);
	}

	if (resetMovement) 
	{
		moving = false;
		Multicast_MoveActorPositionInReverse(DeltaTime, inicialPosition);
	}
}

void ARoom3_Actor_Symbols::Multicast_MoveActorPosition_Implementation(float DeltaTime, float targetPosition)
{
	FVector currentLocation = GetActorLocation();

	// Smoothly move the door down towards the target X position
	currentLocation.X = FMath::FInterpTo(currentLocation.X, targetPosition, DeltaTime, moveSpeed);
	SetActorLocation(currentLocation);

	// Stop opening when we reach the target position
	if (FMath::IsNearlyEqual(currentLocation.X, targetPosition, 1.0f))
	{
		moving = false;
	}
}

void ARoom3_Actor_Symbols::Multicast_MoveActorPositionInReverse_Implementation(float DeltaTime, float targetPosition)
{
	FVector currentLocation = GetActorLocation();

	// Smoothly move the door down towards the target X position
	currentLocation.X = FMath::FInterpTo(currentLocation.X, targetPosition, DeltaTime, moveSpeed);
	SetActorLocation(currentLocation);

	// Stop opening when we reach the target position
	if (FMath::IsNearlyEqual(currentLocation.X, targetPosition, 1.0f))
	{
		resetMovement = false;
	}
}

void ARoom3_Actor_Symbols::Interact()
{
	// move the symbol
	moving = true;

	Server_Play2DSound(interactController);

	symbolsManager->CheckSequenceOfSymbols(this);
}

void ARoom3_Actor_Symbols::Server_Play2DSound_Implementation(APlayerController* InteractingController)
{
	if (InteractingController)
	{
		ATheForgottenTrialsPlayerController* myPlayerController = Cast<ATheForgottenTrialsPlayerController>(InteractingController);
		if (myPlayerController)
		{
			myPlayerController->ClientPlaySounds(this, buttonSound, 1.0f, 1.0f, 0.0f);
		}
	}
}

void ARoom3_Actor_Symbols::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		AController* playerController = OtherActor->GetInstigatorController();
		if (!playerController) return;

		APlayerController* overlappingPlayerController = Cast<APlayerController>(playerController);

		interactController = overlappingPlayerController;
	}
}

void ARoom3_Actor_Symbols::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoom3_Actor_Symbols, moving);
	DOREPLIFETIME(ARoom3_Actor_Symbols, resetMovement);
}