// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameLessonGameMode.h"
#include "GameLessonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GoldenScoreCube.h"
#include "RedScoreCube.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h" // 包含定时器管理器
#include "MyPlayerState.h"
#include "MyPlayerController.h"

AGameLessonGameMode::AGameLessonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	BasicScore = 50;

	// 设置默认时间限制为 60 秒
	TimeLimit = 10.0f;
	TimeRemaining = TimeLimit;
}

void AGameLessonGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 随机生成几个方块
	SpawnRandomScoreCubes(5);  // 比如随机生成 5 个方块

	// 启动计时器
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameLessonGameMode::OnTimeUp, TimeLimit, false);
}

void AGameLessonGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameLessonGameMode::OnTimeUp()
{
 	// 游戏结束时触发的操作（结算）
	UE_LOG(LogTemp, Log, TEXT("Time's up! Game Over!"));

	// 结束游戏
	EndGame();
}

float AGameLessonGameMode::GetTimeRemaining() const{
	return TimeRemaining;
}

void AGameLessonGameMode::DisplayScore(){
	// 获取所有玩家的分数
	for (const TPair<int32, int32>& Pair : PlayerScores) {
		int32 PlayerId = Pair.Key;
		int32 Score = Pair.Value;
		// 输出玩家的名称和分数
		UE_LOG(LogTemp, Log, TEXT("Player: %d, Score: %d"), PlayerId, Score);
	}
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
		if (MyPlayerState) {
			MyPlayerState->DisplayScore();
		}
	}
	
}

void AGameLessonGameMode::EndGame()
{
	// 游戏结束时的处理（例如，暂停游戏或显示胜利/失败界面）
	// 显示玩家得分，可以在这里调用 HUD 或 UMG UI 来显示得分
	DisplayScore();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetPause(true); // 暂停游戏
	}
}

void AGameLessonGameMode::UpdatePlayerScores(int32 PlayerId, int32 PlayerScore) {
	if (PlayerScores.Contains(PlayerId)) {
		PlayerScores[PlayerId] = PlayerScore;
	}
	else {
		PlayerScores.Add(PlayerId, PlayerScore);
	}
}

TMap<int32, int32> AGameLessonGameMode::GetPlayerScores() const {
	return PlayerScores;
}

void AGameLessonGameMode::SpawnRandomScoreCubes(int32 Count)
{
	// 获取当前世界
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < Count; i++)
		{
			// 随机生成一个没有重叠的位置
			FVector SpawnLocation = GetNonOverlappingLocation();

			// 随机选择 GoldenScoreCube 或 RedScoreCube
			if (FMath::RandBool())  // 如果是 true，生成 GoldenScoreCube，否则生成 RedScoreCube
			{
				World->SpawnActor<AGoldenScoreCube>(SpawnLocation, FRotator::ZeroRotator);
			}
			else
			{
				World->SpawnActor<ARedScoreCube>(SpawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

// 检查是否有其他 Actor 重叠
bool AGameLessonGameMode::CheckForOverlap(const FVector& Location)
{
	FHitResult HitResult;
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(FVector(100.f, 100.f, 100.f)); 
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);  // 忽略当前 Actor

	// 使用 SweepSingleByChannel 来检查碰撞
	return GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECC_Visibility, CollisionShape, QueryParams);
}

// 随机生成并检查重叠直到成功
FVector AGameLessonGameMode::GetNonOverlappingLocation()
{
	FVector RandomLocation = FVector(
		FMath::RandRange(100.0f, 2900.0f),  // 重新随机 X 轴位置
		FMath::RandRange(100.0f, 2900.0f),  // 重新随机 Y 轴位置
		50.0f  // 固定 Z 轴高度
	);

	// 尝试多次生成直到找到一个不重叠的位置
	int32 AttemptCount = 0;
	while (CheckForOverlap(RandomLocation) && AttemptCount < 1)
	{
		// UE_LOG(LogTemp, Log, TEXT("Change Location!"));
		RandomLocation = FVector(
			FMath::RandRange(100.0f, 2900.0f),  // 重新随机 X 轴位置
			FMath::RandRange(100.0f, 2900.0f),  // 重新随机 Y 轴位置
			50.0f  // 固定 Z 轴高度
		);
		AttemptCount++;
	}

	return RandomLocation;  // 返回最终的位置
}
