#include "AudioTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAudioTriggerVolume::AAudioTriggerVolume()
{
    // Create a root component to allow movement
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // Initialize the trigger box and attach it to the root
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(Root);

    // Make the trigger box visible in the editor
    TriggerBox->SetHiddenInGame(true);
    TriggerBox->SetVisibility(true);

    // Set the trigger box mobility to movable
    TriggerBox->SetMobility(EComponentMobility::Movable);

    // Configure collision properties
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Bind overlap events
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAudioTriggerVolume::OnOverlapBegin);

    // Default values for the sound and play tracking
    TriggerSound = nullptr;
    bHasPlayed = false;
}

// Called when the game starts or when spawned
void AAudioTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAudioTriggerVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APawn::StaticClass()) && !bHasPlayed)
    {
        if (TriggerSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, TriggerSound, GetActorLocation());
            bHasPlayed = true;
        }
    }
}

