// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingHUD.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class GAMELESSON_API ULoadingHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* LoadingProgressBar;
	
};
