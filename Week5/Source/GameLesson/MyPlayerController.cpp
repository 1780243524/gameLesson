// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "GameLessonGameMode.h"

AMyPlayerController::AMyPlayerController()
{
    // ����Ĭ������
    bIsSettled = false;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ��������ӳ�ʼ�����룬���ߴ������������߼�

    AMyPlayerState* MyState = GetPlayerState<AMyPlayerState>();
    if (MyState)
    {
        // ���ó�ʼ����
        MyState->SetCustomScore(0);
        // ��ȡ��ǰ��ҵ� PlayerId
        // FString PlayerUniqueName = GetPlayerState<AMyPlayerState>()->CustomPlayerName;
        // �����ҵ� PlayerId
       //  UE_LOG(LogTemp, Log, TEXT("Player Unique ID: %s"), *PlayerUniqueName);
    }
}