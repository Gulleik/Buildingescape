// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Opendoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORSOK2_API UOpendoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpendoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	UPROPERTY(EditAnywhere)
	float angle = 90.0f;

	UPROPERTY(EditAnywhere)
	float Triggerlimit = 50.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PreasurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float DoorLastOpenTime;

	AActor* Door;

	float getTotalMassOfActorsOnPlate();
};
