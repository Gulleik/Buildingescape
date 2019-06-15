// Fill out your copyright notice in the Description page of Project Settings.

#include "Positionrepor1.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionrepor1::UPositionrepor1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void UPositionrepor1::BeginPlay()
{
	Super::BeginPlay();
	FString navn = GetOwner()->GetName();
	FVector ObjectLocation = GetOwner()->GetActorLocation();
	FString ObjectLocationX = FString::SanitizeFloat(ObjectLocation.X);
	FString ObjectLocationY = FString::SanitizeFloat(ObjectLocation.Y);
	FString ObjectLocationZ = FString::SanitizeFloat(ObjectLocation.Z);
	UE_LOG(LogTemp, Warning, TEXT("%s er i, X=%s, Y=%s, Z=%s "), *navn, *ObjectLocationX, *ObjectLocationY, *ObjectLocationZ);
	// ...
	
}


// Called every frame
void UPositionrepor1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

