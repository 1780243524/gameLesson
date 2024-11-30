// Fill out your copyright notice in the Description page of Project Settings.


#include "RedScoreCube.h"
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
ARedScoreCube::ARedScoreCube()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // 使用碰撞盒作为碰撞组件
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // 设置碰撞配置
    BoxComponent->SetCollisionProfileName("BlockAll");

    // 绑定碰撞事件到 OnHit 函数
    BoxComponent->OnComponentHit.AddDynamic(this, &ARedScoreCube::OnHit);

    // 创建静态网格组件以使方块在关卡中可见
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // 为网格设置默认的静态网格
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    // 加载红色材质
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> RedMaterialFinder(TEXT("Material'/Game/Material/M_RedMaterial.M_RedMaterial'"));
    UE_LOG(LogTemp, Log, TEXT("Loading Red!"));
    if (RedMaterialFinder.Succeeded()) {
        UE_LOG(LogTemp, Log, TEXT("Red!"));
        UMaterialInterface* RedMaterial = RedMaterialFinder.Object;
        MeshComponent->SetMaterial(0, RedMaterial);
    }

    // 设置网格的材质
    MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // 设置网格缩放大小
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 只让碰撞盒处理碰撞

    // 启用重叠事件
    BoxComponent->SetNotifyRigidBodyCollision(true);

    // 初始化变量
    HitCount = 0;
}

// Called when the game starts or when spawned
void ARedScoreCube::BeginPlay()
{
    Super::BeginPlay();
    // 确保网格组件存在
    if (MeshComponent)
    {
        // 启用物理模拟
        MeshComponent->SetSimulatePhysics(true);

        // 启用重力
        MeshComponent->SetEnableGravity(true);

        // 设置质量
        MeshComponent->SetMassOverrideInKg(NAME_None, 10.0f);  // 设置质量为 10kg
    }
}

// Called every frame
void ARedScoreCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// 当投射物（子弹）击中这个方块时调用
void ARedScoreCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
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
                    int32 ScoreToAdd = BasicScore;
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
