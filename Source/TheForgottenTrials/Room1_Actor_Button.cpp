// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_Button.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include <Net/UnrealNetwork.h>


// Sets default values
ARoom1_Actor_Button::ARoom1_Actor_Button()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the ProximityBox
	proximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	proximityBox->SetupAttachment(RootComponent);
	proximityBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	proximityBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom1_Actor_Button::OnOverlapBegin);
	proximityBox->OnComponentEndOverlap.AddDynamic(this, &ARoom1_Actor_Button::OnOverlapEnd);

	// Initialize the KeypadMesh
	buttonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("buttonMesh"));
	buttonMesh->SetupAttachment(RootComponent);

	playerInRange = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ARoom1_Actor_Button::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom1_Actor_Button::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (moving)
	{
		MoveButton(DeltaTime);
	}
}

void ARoom1_Actor_Button::MoveButton(float DeltaTime)
{
	if (yAxis) 
	{
		FVector currentLocation = buttonMesh->GetComponentLocation();
		currentLocation.Y = FMath::FInterpTo(currentLocation.Y, targetXPosition, DeltaTime, moveSpeed);
		buttonMesh->SetWorldLocation(currentLocation);

		if (FMath::IsNearlyEqual(currentLocation.Y, targetXPosition, 1.0f))
		{
			moving = false;

			targetFinalDoor->OpenDoor();
		}
	}
	else 
	{
		FVector currentLocation = buttonMesh->GetComponentLocation();
		currentLocation.X = FMath::FInterpTo(currentLocation.X, targetXPosition, DeltaTime, moveSpeed);
		buttonMesh->SetWorldLocation(currentLocation);

		if (FMath::IsNearlyEqual(currentLocation.X, targetXPosition, 1.0f))
		{
			moving = false;

			targetFinalDoor->OpenDoor();
		}
	}
	
}

void ARoom1_Actor_Button::Interact()
{
	if (playerInRange && targetFinalDoor)
	{
		moving = true;

		Multicast_Play2DSound();
	}
}

void ARoom1_Actor_Button::Multicast_Play2DSound_Implementation()
{
	if (buttonSound)
	{
		UGameplayStatics::PlaySound2D(this, buttonSound, 1.0f /*Volume*/, 1.0f /*Pitch*/, 0.0f /*StartTime*/);
	}
}

void ARoom1_Actor_Button::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		playerInRange = true;
	}
}

void ARoom1_Actor_Button::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		playerInRange = false;
	}
}

void ARoom1_Actor_Button::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoom1_Actor_Button, moving);
}