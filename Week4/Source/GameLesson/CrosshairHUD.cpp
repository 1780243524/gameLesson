// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairHUD.h"
#include "TimerManager.h"
#include "Components/Border.h"

void UCrosshairHUD::TurnRed()
{
    // 检查 4 个 Border 是否有效
    if (BottomCrosshair && TopCrosshair && LeftCrosshair && RightCrosshair)
    {
        // 设置所有 Border 的颜色为红色
        FLinearColor RedColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
        BottomCrosshair->SetBrushColor(RedColor);
        TopCrosshair->SetBrushColor(RedColor);
        LeftCrosshair->SetBrushColor(RedColor);
        RightCrosshair->SetBrushColor(RedColor);
        // UE_LOG(LogTemp, Log, TEXT("Crosshair brush turn to red"));
    }
}

// 恢复颜色
void UCrosshairHUD::TurnWhite()
{
    // 设置颜色到白色
    FLinearColor DefaultColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f); // 白色
    BottomCrosshair->SetBrushColor(DefaultColor);
    TopCrosshair->SetBrushColor(DefaultColor);
    LeftCrosshair->SetBrushColor(DefaultColor);
    RightCrosshair->SetBrushColor(DefaultColor);
}



