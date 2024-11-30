// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldenScoreCube.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameLessonProjectile.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerState.h"
#include "GameLessonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "GameLessonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoldenScoreCube::AGoldenScoreCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // 使用碰撞盒作为碰撞组件
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // 设置碰撞配置
    BoxComponent->SetCollisionProfileName("BlockAll");

    // 绑定碰撞事件到 OnHit 函数
    BoxComponent->OnComponentHit.AddDynamic(this, &AGoldenScoreCube::OnHit);

    // 创建静态网格组件以使方块在关卡中可见
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // 为网格设置默认的静态网格
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    // 加载金色材质
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> GoldenMaterialFinder(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold'"));
    UE_LOG(LogTemp, Log, TEXT("Loading Golden!"));
    if (GoldenMaterialFinder.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("Golden!"));
        UMaterialInterface* GoldenMaterial = GoldenMaterialFinder.Object;
        MeshComponent->SetMaterial(0, GoldenMaterial);
    }


    // 设置网格的材质
    MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // 设置网格缩放大小
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 只让碰撞盒处理碰撞

    // 初始化变量
    HitCount = 0;
}

// Called when the game starts or when spawned
void AGoldenScoreCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldenScoreCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// 当投射物（子弹）击中这个方块时调用
void AGoldenScoreCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    // 检查碰撞的其他物体是否是投射物（子弹）
    // 获取当前的 GameMode 实例
    
    if (OtherActor && OtherActor->IsA(AGameLessonProjectile::StaticClass())) {
        // 获取射击投射物的玩家
        if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
            // 将 PlayerState 强制转换为 AMyPlayerState
            AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerController->PlayerState);
            if (MyPlayerState)
            {
                // 增加分数
                // 获取 GameMode 中的 BasicScore 变量
                AGameLessonGameMode* GameMode = Cast<AGameLessonGameMode>(UGameplayStatics::GetGameMode(this));
                if (GameMode) {
                    int32 BasicScore = GameMode->BasicScore;
                    int32 ScoreToAdd = BasicScore * 2;
                    MyPlayerState->IncreaseCustomScore(ScoreToAdd);
                    UE_LOG(LogTemp, Log, TEXT("CustomScore Increased by hitting ScoreCube! Score Added: %d"), ScoreToAdd);
                }
                
            }
        }

        // 销毁投射物
        OtherActor->Destroy();

        // 增加被击中的次数
        HitCount++;

        // 根据被击中的次数执行不同的操作
        if (HitCount == 1) {
            // 第一次被击中时，缩小网格大小为原来的 1/2
            FVector CurrentScale = MeshComponent->GetComponentScale();
            MeshComponent->SetWorldScale3D(CurrentScale * 0.5f);
            UE_LOG(LogTemp, Log, TEXT("ScoreCube hit once, scale reduced to half!"));
        }
        else if (HitCount >= 2) {
            // 第二次被击中时，销毁方块
            UE_LOG(LogTemp, Log, TEXT("ScoreCube hit twice, destroyed!"));
            Destroy();
        }
    }
}
