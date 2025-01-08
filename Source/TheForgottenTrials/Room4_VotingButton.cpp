// Fill out your copyright notice in the Description page of Project Settings.


#include "Room4_VotingButton.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FinalRoomLogic.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ARoom4_VotingButton::ARoom4_VotingButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProximityBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProximityBox"));
	ProximityBox->SetupAttachment(RootComponent);
	ProximityBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	ProximityBox->OnComponentBeginOverlap.AddDynamic(this, &ARoom4_VotingButton::OnOverlapBegin);
	ProximityBox->OnComponentEndOverlap.AddDynamic(this, &ARoom4_VotingButton::OnOverlapEnd);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(RootComponent);

	bPlayerInRange = false;

    bReplicates = true;
}

// Called when the game starts or when spawned
void ARoom4_VotingButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom4_VotingButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (moving)
    {
		MoveButton(DeltaTime);
    }
}

void ARoom4_VotingButton::Interact()
{
    if (!FinalRoomLogic)
    {
        return;
    }

    if (bPlayerInRange)
    {
		//Check if the character has pressed any buttons
        if (alreadyVoted)
        {
            return;
        }

        Play2DSound();

        moving = true;

		//Set this button to already voted
		alreadyVoted = true;

		//Set the other button to already voted
		otherButton->alreadyVoted = true;

        if (characterName == "Ethan_C_0")
        {
            EthanButtons(characterName);
        }

        if (characterName == "Isabel_C_0")
        {
            IsabelButtons(characterName);
        }
    }
}

void ARoom4_VotingButton::EthanButtons(FString character)
{
    FinalRoomLogic->RegisterVote(character, VoteFor);
}

void ARoom4_VotingButton::IsabelButtons(FString character)
{
    FinalRoomLogic->RegisterVote(character, VoteFor);
}

void ARoom4_VotingButton::MoveButton(float DeltaTime)
{
    FVector currentLocation = ButtonMesh->GetComponentLocation();
    currentLocation.Y = FMath::FInterpTo(currentLocation.Y, targetYPosition, DeltaTime, moveSpeed);
    ButtonMesh->SetWorldLocation(currentLocation);

    if (FMath::IsNearlyEqual(currentLocation.Y, targetYPosition, 1.0f))
    {
        moving = false;
    }
}

void ARoom4_VotingButton::Play2DSound()
{
    if (buttonSound)
    {
        UGameplayStatics::PlaySound2D(this, buttonSound, 1.0f /*Volume*/, 1.0f /*Pitch*/, 0.0f /*StartTime*/);
    }
}

void ARoom4_VotingButton::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        bPlayerInRange = true;

        ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor);
        if (OverlappingCharacter)
        {
            characterName = OverlappingCharacter->GetName();
        }
    }
}

void ARoom4_VotingButton::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        bPlayerInRange = false;
    }
}

void ARoom4_VotingButton::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ARoom4_VotingButton, moving);
    DOREPLIFETIME(ARoom4_VotingButton, alreadyVoted);
}