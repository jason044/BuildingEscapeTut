// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
	
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
	{
		PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

		if (PhysicsHandle)
		{
			// physics handle is found
		}
		/*
		else
		{
			UE_LOG (LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName(0))
		}
		*/
	}

/// Look for attached input component (only appears at runtime)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("input component found"))
		/// bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	/*
	else
	{
		UE_LOG (LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName(0))
	}
	*/
}



void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

		/// line trace and see if we reach any actors with physics body colision channel set
		GetFirstPhysicsBodyInReach();

		/// if we hit something then attach a physics handle
		//TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))
		//TODO release physics handle
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the physics handle is attached
		//move the object that we're holding 

	


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	//Log out to test NOT WORKING
		//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		//*PlayerViewpointLocation.ToString(),
		//*PlayerViewpointRotation.ToString()
		//)

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	///Set up query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());



	/// raycast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line tace hit: %s"), *(ActorHit->GetName()))
	}
	return FHitResult();
}