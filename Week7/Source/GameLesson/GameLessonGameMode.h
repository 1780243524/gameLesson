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

	// ������ɵ÷ַ���
	void SpawnRandomScoreCubes(int32 Count);

	// ���л����÷�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 BasicScore;

	// �õ���ǰʣ��ʱ��
	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetTimeRemaining() const;

	// �õ��������ֵ
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetMaxHealth() const;

	// �õ���ʼ����ֵ
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetStartHealth() const;

	// ��ʾ����
	void DisplayScore();

protected:
	virtual void BeginPlay() override;

private:
	// ����Ƿ������� Actor �ص�
	bool CheckForOverlap(const FVector& Location);

	// ������ɲ�����ص�ֱ���ɹ�
	FVector GetNonOverlappingLocation();

	// ʱ�䵽ʱ���õĺ���
	void OnTimeUp();

	// ��Ϸ����ʱ�Ĳ���
	void EndGame();

	// ��ʱ�����
	FTimerHandle TimerHandle;

	// ��Ϸʱ��
	float TimeLimit;

	// ʣ��ʱ��
	float TimeRemaining;

	// ��ҳ�ʼ����ֵ
	int32 StartHealth;

	// ����������ֵ
	int32 MaxHealth;
};



