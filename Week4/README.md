# Week4

## UE中的UI实现

### SlateUI

Slate是UE的底层UI框架，所有UI的基础，需要编写大量的C++代码来实现UI。

### UMG

UE的可视化UI工具，底层依赖于Slate进行UI渲染和交互处理。

画布：所见即所得。

细节面板：用于调整UI元素的属性。

动画轨道：用于编辑控件动画。

图表：可以实现蓝图可视化编程。

### UMG蓝图制作要点

元素展现：通过图片、文字等内容，直观的展现UI需要表述的信息。

交互体验：使用按钮、滑动条、输入框等交互元素获取玩家输入以达成交互成就。

布局调整与适配：通过合理的布局来保证用户体验。

动画效果：通过动画效果提升美观。

功能实现：以代码进行功能驱动。

PreConstruct：不安全，没在运行的时候就会执行。

Construct：更安全。

OnInitialized：可以做绑定事件的操作，因为只会触发一次。

### C++绑定控件蓝图

1. 首先创建继承UserWidget的C++类；

2. 修改WidgetBlueprint中类设置里的父类为刚才创建的C++类；

3. 在C++头文件里绑定对应的变量，用UPROPERTY()。
    注意点：Ctrl alt f11是热编译；头文件里一般不建议include其他新的头文件，所以当在头文件里遇到需要引入其他类时，可以在头文件顶部预先定义一个class如：class UTextButton。

4. 绑定函数时最好重载NativeOnInitialized函数，在这个函数中进行绑定，因为他会调用OnInitialized，只会执行一次。使用AddDynamic绑定。

### 进阶技巧

Slot：进行一些细节的调整，相关于父节点做的调整。

锚点：用来保证空间的相对位置。

## 作业

实现登录界面：输入用户名和密码，密码加密显示，有确认按钮。

实现加载界面：要有动画表示正在加载。

实现射击游戏操作面板：血条，子弹数，击中方块会发生变化的准星。