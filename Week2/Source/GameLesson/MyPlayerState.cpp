// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"



AMyPlayerState::AMyPlayerState()
{
    CustomScore = 0;
    PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
    int32 PlayerUniqueId = GetWorld()->GetFirstPlayerController()->PlayerState->GetPlayerId();
    GameMode->UpdatePlayerScores(PlayerUniqueId, CustomScore);
}

// ���÷���
void AMyPlayerState::SetCustomScore(int32 NewScore)
{
    if (CustomScore != NewScore)
    {
        CustomScore = NewScore;
        // ����OnRep_Score�ص�
        OnRep_Score();
    }
}

int32 AMyPlayerState::GetCustomScore() const
{
    return CustomScore;
}

void AMyPlayerState::IncreaseCustomScore(int32 Amount) {
    SetCustomScore(CustomScore + Amount);
    UE_LOG(LogTemp, Log, TEXT("Score Increased: %d"), GetCustomScore());
}

void AMyPlayerState::DisplayScore() {
    UWorld* World = GetWorld();
    if (World)
    {
        
    }
}

void AMyPlayerState::OnRep_Score()
{
    // ������������UI���»�����������
    // UE_LOG(LogTemp, Log, TEXT("Player score updated: %d"), Score);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyPlayerState, CustomScore);
}

