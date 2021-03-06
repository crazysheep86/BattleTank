// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("Tank Controlled: None"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank Controlled: %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return;}
    
    FVector HitLocation; // Out parameter
    
    if(GetSightRayHitLocation(HitLocation))
    {
        
        GetControlledTank()->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
    //Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line trace along that look direction, and see what we hit (up to max range)
        if(GetLookVectorHitLocation(LookDirection, HitLocation))
        {
            //UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
        }
        
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // To be discarded
    
    //"de-project" the screen position of the crosshair to a world direction
    return DeprojectScreenPositionToWorld(ScreenLocation.X,
                                   ScreenLocation.Y,
                                   CameraWorldLocation,
                                   LookDirection);
    
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        // Set hit Location
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; //Line trace didn't suceed
    
}
