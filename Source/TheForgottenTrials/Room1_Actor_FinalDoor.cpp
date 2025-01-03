// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1_Actor_FinalDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ARoom1_Actor_FinalDoor::ARoom1_Actor_FinalDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = doorMesh;
	doorMesh->SetIsReplicated(true);

	DoorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorTriggerBox"));
	DoorTriggerBox->SetupAttachment(RootComponent);
	DoorTriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	DoorTriggerBox->SetMobility(EComponentMobility::Static);
	DoorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom1_Actor_FinalDoor::OnTriggerBeginOverlap);
	DoorTriggerBox->OnComponentEndOverlap.AddDynamic(this, &ARoom1_Actor_FinalDoor::OnTriggerEndOverlap);

	rotationSpeed = 2.0f;
	rotating = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ARoom1_Actor_FinalDoor::BeginPlay()
{
	Super::BeginPlay();
	
	initialRotation = GetActorRotation();
}

// Called every frame
void ARoom1_Actor_FinalDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (rotating)
	{
		FRotator currentRotation = GetActorRotation();
		FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, DeltaTime, rotationSpeed);
		SetActorRotation(newRotation);

		if (currentRotation.Equals(targetRotation, 1.0f))
		{
			rotating = false;
		}
	}
}

void ARoom1_Actor_FinalDoor::OpenDoor()
{
	rotating = true;
	targetRotation = initialRotation + FRotator(0.0f, -90.0f, 0.0f);
}

void ARoom1_Actor_FinalDoor::CloseDoor()
{
	//if (rotating) return;

	rotating = true;
	targetRotation = initialRotation;
}

void ARoom1_Actor_FinalDoor::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,UPrimitiveComponent * OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		
	}
}


	// Called when another actor exits the trigger box
void ARoom1_Actor_FinalDoor::OnTriggerEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		CloseDoor();
		
	}
}

void ARoom1_Actor_FinalDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoom1_Actor_FinalDoor, rotating);
}