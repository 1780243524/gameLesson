// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMELESSON_API PlayerScores
{
public:
    USTRUCT(BlueprintType)
        struct FPlayerScore
    {
        UPROPERTY(Replicated)
        int32 PlayerId;

        UPROPERTY(Replicated)
        int32 Score;

        FPlayerScore() : PlayerId(0), Score(0) {}
    };

	PlayerScores();
	~PlayerScores();
};
