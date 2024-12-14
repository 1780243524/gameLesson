// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairHUD.h"
#include "TimerManager.h"
#include "Components/Border.h"

void UCrosshairHUD::TurnRed()
{
    // ��� 4 �� Border �Ƿ���Ч
    if (BottomCrosshair && TopCrosshair && LeftCrosshair && RightCrosshair)
    {
        // �������� Border ����ɫΪ��ɫ
        FLinearColor RedColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); // ��ɫ
        BottomCrosshair->SetBrushColor(RedColor);
        TopCrosshair->SetBrushColor(RedColor);
        LeftCrosshair->SetBrushColor(RedColor);
        RightCrosshair->SetBrushColor(RedColor);
        // UE_LOG(LogTemp, Log, TEXT("Crosshair brush turn to red"));
    }
}

// �ָ���ɫ
void UCrosshairHUD::TurnWhite()
{
    // ������ɫ����ɫ
    FLinearColor DefaultColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f); // ��ɫ
    BottomCrosshair->SetBrushColor(DefaultColor);
    TopCrosshair->SetBrushColor(DefaultColor);
    LeftCrosshair->SetBrushColor(DefaultColor);
    RightCrosshair->SetBrushColor(DefaultColor);
}



