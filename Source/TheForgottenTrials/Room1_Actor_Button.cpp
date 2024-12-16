// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_Button.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"


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

}

void ARoom1_Actor_Button::Interact()
{
	if (playerInRange && targetFinalDoor)
	{
		targetFinalDoor->OpenDoor();
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

