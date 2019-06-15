// Fill out your copyright notice in the Description page of Project Settings.

#include "Positionreport.h"

// Sets default values for this component's properties
UPositionreport::UPositionreport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UPositionreport::BeginPlay()
{
	Super::BeginPlay();
		UE_LOG(LogTemp, Warning, TEXT("positionreport"));
	// ...
	
}


// Called every frame
void UPositionreport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

