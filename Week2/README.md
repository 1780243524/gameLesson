# Week2

## 课程笔记

### Uobject

元数据，反射上次，GC，序列化，通用的属性和接口，UE引擎中的描述物体基础。

### Actor + ActorComponent

EC架构设计模式，即插即用。

SceneComponent是ActorComponent的派生类，会赋予ActorComponent的空间变换信息。

### UWorld + ULevel

用来表达世界。

为什么要有Level：因为没法一次性把所有的东西都加载到一个World中。

平行世界：GameWorld，PIEWorld（编辑器中世界），PreviewWorld（预览世界）。

关卡构成：RersistenLevel（主关卡）+子关卡。

关卡加载：流式异步加载。

关卡大小和加载距离：LevelBounds +StreamingDistance分层。

关卡蓝图：定义关卡规则。

### UGameInstance + UEngine

在世界之上的内容

UGameInstance：信息存在整个游戏生命周期，用于全局管理。

UEngine：管理游戏以及用于拉起游戏世界。

### AActor

RootComponent提供世界变化信息。

作为网络同步的基础单位。

Owner指针标志所有权。

Role枚举标志本地权限。

两种Actor：

1. 关卡内摆放的静态Actor。
2. SpawnActor创建的动态Actor。

重要生命周期函数：

1. BeginPlay。
2. EndPlay。
3. Tick。

Actor的Destory：GC完成收尾工作。

## APawn

可操控的棋子。

架构：可以被Controller控制，具有基础的输入、移动框架支持，生产者消费者框架。

常用的派生类：

1. ADefaultPawn：基础的Pawn，具有简单球形碰撞等功能。
2. ASpectatorPawn：观战的Pawn，不会外显。

### ACharactor

人形角色。

近似仿真人形的胶囊体碰撞盒，具有骨骼模型，具有人物移动组件。

### AController

通过Possess来控制APawn的PossessedBy。

### APlayerController

玩家的控制器。

UInputComponent：绑定输入映射。

AHUD：头显，与UI的区别是不可交互，且为半透明。

具有网络连接所有权（只有主控端和服务端具有PlayerController）。

### AGameMode

游戏模式。

仅服务器拥有，掌控整体游戏流程（所以单机游戏没有）。

定义游戏模式的基础类型。

纯服务器逻辑的运作，如AI。

是AGameModeBase的派生类。

### AGameState

游戏状态。

所有端都共享同步的游戏数据。

是AGameStateBase的派生类，更适用于对抗类游戏。

### APlayerState

玩家状态。

## 第二周作业

实现一个游戏Demo：

1. 物件规则：

   射击命中方块，获得积分X分。

   方块被子弹命中后，缩放为Y倍，再次命中后被销毁。

2. 游戏流程：

   游戏开始时随机N个方块成为重要目标，射击后得到双倍积分。

   游戏开始后限时T秒，时间到后游戏结算，打印日志输出每个玩家获得的总积分和所有玩家获得的总积分。

3. 附加题：

   利用UMG制作结算UI替代打印日志。

   支持多人联机。

## 说明

Source文件夹中保存了项目源码；Android_ASTC中保存了安卓apk文件。

实现的功能：

1. 射击命中红色方块，获得积分50分；射击命中金色方块，获得积分100分；
2. 击中方块后方块会缩小1倍，再次击中会消失；
3. 游戏开始时在随机地点生成5个方块，其中会有随机个数个方块金色方块；
4. 游戏界面右上角会显示玩家分数，正上方会显示游戏剩余时间；
5. 游戏时间结束自动暂停游戏，同时服务端打印所有用户的得分。