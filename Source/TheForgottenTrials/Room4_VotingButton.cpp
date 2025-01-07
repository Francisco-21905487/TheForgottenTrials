// Fill out your copyright notice in the Description page of Project Settings.


#include "Room4_VotingButton.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FinalRoomLogic.h"


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

}

void ARoom4_VotingButton::Interact()
{
    if (bPlayerInRange && FinalRoomLogic)
    {
        FinalRoomLogic->RegisterVote(VoteFor);  // Notify FinalRoomLogic about the vote
    }
}

void ARoom4_VotingButton::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))  // Ensure it's the player
    {
        bPlayerInRange = true;
    }
}

void ARoom4_VotingButton::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))  // Ensure it's the player
    {
        bPlayerInRange = false;
    }
}

