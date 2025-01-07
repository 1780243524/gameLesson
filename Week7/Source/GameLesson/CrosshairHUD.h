// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairHUD.generated.h"

/**
 * 
 */

class UBorder;
UCLASS()
class GAMELESSON_API UCrosshairHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* BottomCrosshair;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* TopCrosshair;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* LeftCrosshair;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* RightCrosshair;

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void TurnRed();

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void TurnWhite();

	FTimerHandle ColorResetTimerHandle;
};
