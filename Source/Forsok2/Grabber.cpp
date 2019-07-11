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

void UGrabber::findPhysicsHandleComponent() {
	///look for physicshandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
	}
	else {
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

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerLocation,
		OUT	PlayerRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *location.ToString(), *Rotation.ToString());
	*/// ...
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	if (PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	}

};

void UGrabber::Grab() {
	auto hitResult = getFirstPhysicsBodyInREach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit) {
		PhysicsHandle->GrabComponentAtLocation(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation()
		);
	}
}
void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();

}




FHitResult UGrabber::getFirstPhysicsBodyInREach() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerLocation,
		OUT	PlayerRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *location.ToString(), *Rotation.ToString());
	*/// ...
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor * ActorHit = hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Object: %s"), *(ActorHit->GetName()));
	};

	return hit;
}
