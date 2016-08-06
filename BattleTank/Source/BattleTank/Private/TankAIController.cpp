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

