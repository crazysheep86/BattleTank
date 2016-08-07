// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto AITargetedTank = GetPlayerTank();
    
    if (!AITargetedTank) {
        UE_LOG(LogTemp, Warning, TEXT("AI Tank Targeted: None"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Tank Targeted: %s"), *(AITargetedTank->GetName()));
    }
    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(GetPlayerTank())
    {
        // TODO Move towards the player
        
        // Aim Towards the player
        GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
        
        // FIRE!
    }
}

ATank* ATankAIController::GetControlledAITank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(!PlayerPawn) { return nullptr;}
    
    return Cast<ATank>(PlayerPawn);
}

