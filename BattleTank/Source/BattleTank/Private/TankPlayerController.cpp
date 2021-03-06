// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Get tank
	ATank* MyTank = GetControlledTank();
	if (!MyTank) { return; }

	FVector HitLocation = FVector(0);

	// Get the screen location of the crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * AimX, ViewportSizeY * AimY);

	// De-project screen position of the crosshair to a world direction
	FVector LookDirection;
	FVector CameraWorldLocation; // To be discarded
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		FHitResult HitResult;
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

		// If we have a hit in the world, set the HitLocation
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
		{
			HitLocation = HitResult.Location;
		}
	}
	MyTank->AimAt(HitLocation);
}
