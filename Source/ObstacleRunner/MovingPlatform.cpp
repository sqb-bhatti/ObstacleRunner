// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();  // Get the start location

	//writing to the output log 
	UE_LOG(LogTemp, Display, TEXT("Configured Move Distance: %f"), MoveDistance);
	// UE_LOG(LogTemp, Warning, TEXT("Your Message"));
	// UE_LOG(LogTemp, Error, TEXT("Your Message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Reverse the direction of motion if gone too far
	if(ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// Move platform forwards
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}



void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Check how far we have moved
	return GetDistanceMoved() > MoveDistance;
}


float AMovingPlatform::GetDistanceMoved() const
{
	// Check how far we have move
	return FVector::Dist(StartLocation, GetActorLocation());
}