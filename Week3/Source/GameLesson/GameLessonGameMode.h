// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameLessonGameMode.generated.h"

UCLASS(minimalapi)
class AGameLessonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameLessonGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 随机生成得分方块
	void SpawnRandomScoreCubes(int32 Count);

	// 击中基本得分
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 BasicScore;

	// 得到当前剩余时间
	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetTimeRemaining() const;

	// 显示分数
	void DisplayScore();

protected:
	virtual void BeginPlay() override;

private:
	// 检查是否有其他 Actor 重叠
	bool CheckForOverlap(const FVector& Location);

	// 随机生成并检查重叠直到成功
	FVector GetNonOverlappingLocation();

	// 时间到时调用的函数
	void OnTimeUp();

	// 游戏结束时的操作
	void EndGame();

	// 定时器句柄
	FTimerHandle TimerHandle;

	// 游戏时长
	float TimeLimit;

	// 剩余时间
	float TimeRemaining;
};



