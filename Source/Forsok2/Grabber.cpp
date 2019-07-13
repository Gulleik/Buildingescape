// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	setupInputComponent();
	findPhysicsHandleComponent();
}

//look for physicshandle
void UGrabber::findPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s : cant find PhysicsHandler"), *GetOwner()->GetName());
	}
}

// look for attached Input Component at runtime
void UGrabber::setupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s : cant find InputComponent"), *GetOwner()->GetName());
	}
}

//Grab action
void UGrabber::Grab() {
	auto hitResult = getFirstPhysicsBodyInREach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit) {
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation()
		);
	}
}

//Release action
void UGrabber::Release() {
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

//Return linetrace in reach
FVector UGrabber::getLineTraceEnd() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewpointLocation,
		OUT	PlayerViewpointRotation
	);
	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
}

//return playerlocation
FVector UGrabber::getLineTraceStart() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewpointLocation,
		OUT	PlayerViewpointRotation
	);
	return PlayerViewpointLocation;
}

//Returning physicsbody in reach
FHitResult UGrabber::getFirstPhysicsBodyInREach() const
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		getLineTraceStart(),
		getLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor * ActorHit = hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Object: %s"), *(ActorHit->GetName()));
	};

	return hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(getLineTraceEnd());
	}

};
