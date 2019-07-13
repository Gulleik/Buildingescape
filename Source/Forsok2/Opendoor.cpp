// Fill out your copyright notice in the Description page of Project Settings.

#include "Opendoor.h"

#define OUT

// Sets default values for this component's properties
UOpendoor::UOpendoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpendoor::BeginPlay()
{
	Super::BeginPlay();
	Door = GetOwner();
}

void UOpendoor::OpenDoor()
{
	Door->SetActorRotation(FRotator(0.f, angle, 0.f));
}

void UOpendoor::CloseDoor()
{
	Door->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpendoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	getTotalMassOfActorsOnPlate();

	if (getTotalMassOfActorsOnPlate() > Triggerlimit)
	{
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime > DoorCloseDelay) 
	{
		CloseDoor();
	}
	// ...
}

float UOpendoor::getTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PreasurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s on preassureplate"), *actor->GetName());
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}

