#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioTriggerVolume.generated.h"

UCLASS()
class THEFORGOTTENTRIALS_API AAudioTriggerVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioTriggerVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    // Box component for collision detection
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* TriggerBox;

    // Sound to play
    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* TriggerSound;

    // Track if the sound has already been played
    bool bHasPlayed;

    // Handle overlap events
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor,class UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

};
