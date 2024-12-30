// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameLessonCharacter.h"
#include "MyPlayerController.h"
#include "BluePrint/UserWidget.h"
#include "SettlementHUD.h"
#include "MyGameState.h"
#include "TimerManager.h"
#include "MyGameInstance.h" 

AMyPlayerState::AMyPlayerState()
{
    PrimaryActorTick.bCanEverTick = true;

    MyGameState = GetWorld() != nullptr ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
    GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));

    CustomScore = 0;
    
    CustomPlayerName = "Tmp";

    bIsHit = false;
    
    if (GameMode) 
    {
        CurrentHealth = GameMode->GetStartHealth();
        MaxHealth = GameMode->GetMaxHealth();
    }
    else 
    {
        CurrentHealth = 100;
        MaxHealth = 100;
        UE_LOG(LogTemp, Log, TEXT("Using dafault health"));
    }
    
}

void AMyPlayerState::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        CustomPlayerName = GameInstance->GetPlayerName();
        UE_LOG(LogTemp, Log, TEXT("Name: %s"), *CustomPlayerName);
    }
}

void AMyPlayerState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (MyGameState)
    {
        MyGameState->UpdatePlayerScores(CustomPlayerName, CustomScore);
    }
   
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

void AMyPlayerState::IncreaseCustomScore(int32 Amount) 
{
    SetCustomScore(CustomScore + Amount);
    UE_LOG(LogTemp, Log, TEXT("Score Increased: %d"), GetCustomScore());
}

void AMyPlayerState::DisplaySettlement() {
    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
    if (PlayerController)
    {
        if (!PlayerController->bIsSettled) 
        {
            PlayerController->bIsSettled = true;
            // UE_LOG(LogTemp, Log, TEXT("IsSettled"));
            // ��ȡ�� PlayerController ������ Pawn����ɫ��
            APawn* PlayerPawn = PlayerController->GetPawn();
            if (PlayerPawn)
            {
                // ��� Pawn �� BP_FirstPersonCharacter ���ͣ�����ת��
                AGameLessonCharacter* FirstPersonCharacter = Cast<AGameLessonCharacter>(PlayerPawn);
                if (FirstPersonCharacter)
                {
                    // UE_LOG(LogTemp, Log, TEXT("Found BP_FirstPersonCharacter"));
                    FString WidgetClassLoadPath = FString(TEXT("/Game/BluePrint/HUD_Settlement.HUD_Settlement_C"));
                    UClass* TmpWidget = LoadClass<UUserWidget>(NULL, *WidgetClassLoadPath);
                    if (TmpWidget)
                    {
                        // UE_LOG(LogTemp, Log, TEXT("TmpWidget"))
                        USettlementHUD* HUD_Settlement = CreateWidget<USettlementHUD>(GetWorld(), TmpWidget);
                        if (HUD_Settlement)
                        {
                            // UE_LOG(LogTemp, Log, TEXT("HUD_Settlement"));
                            HUD_Settlement->AddScore();
                            HUD_Settlement->AddToViewport();
                            // ������Ϊ��ͼģʽ��ȷ�������ᱻ����UI�ڵ�
                            PlayerController->bShowMouseCursor = true;  // �����ϣ����ʾ���ָ��
                            PlayerController->SetInputMode(FInputModeUIOnly());  // ��������ģʽΪ UI ģʽ
                        }
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Player's pawn is not of type BP_FirstPersonCharacter"));
                }
            }
        }
        
    }
}

void AMyPlayerState::OnRep_Score()
{
    // ������������UI���»�����������
    // UE_LOG(LogTemp, Log, TEXT("Player score updated: %d"), Score);
}

int32 AMyPlayerState::GetCurrentHealth() const
{
    return CurrentHealth;
}

void AMyPlayerState::SetCurrentHealth(int32 NewHealth)
{
    if (NewHealth > MaxHealth) 
    {
        CurrentHealth = MaxHealth;
    }
    else if (NewHealth < 0)
    {
        CurrentHealth = 0;
    }
    else
    {
        CurrentHealth = NewHealth;
    }
}

void AMyPlayerState::HitTarget() 
{
    bIsHit = true;
    // UE_LOG(LogTemp, Log, TEXT("bIsHit true"));
    // ���ü�ʱ�������ڻָ�ԭʼ��ɫ
    GetWorld()->GetTimerManager().SetTimer(
        IsHitResetTimerHandle,
        this,
        &AMyPlayerState::ResetIsHit,
        0.2f,
        false
    );
}

void AMyPlayerState::ResetIsHit()
{
    // UE_LOG(LogTemp, Log, TEXT("bIsHit false"));
    bIsHit = false;
}