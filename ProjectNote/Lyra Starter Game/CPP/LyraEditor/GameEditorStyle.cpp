//C:\Users\chru\Desktop\Lyra\Source\LyraEditor\Private

// 定义一个宏，用于创建图像画刷
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(FPaths::EngineContentDir() / "Editor/Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)

// 定义一个宏，用于创建方形容器画刷
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(FPaths::EngineContentDir() / "Editor/Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)

// 定义一个宏，用于创建边框画刷
#define BORDER_BRUSH(RelativePath, ...) FSlateBorderBrush(FPaths::EngineContentDir() / "Editor/Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)

// 定义一个宏，用于创建游戏图像画刷
#define GAME_IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(FPaths::ProjectContentDir() / "Editor/Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)

// 定义一个宏，用于创建游戏图像画刷（SVG格式）
#define GAME_IMAGE_BRUSH_SVG(RelativePath, ...) FSlateVectorImageBrush(FPaths::ProjectContentDir() / "Editor/Slate" / RelativePath + TEXT(".svg"), __VA_ARGS__)

/*
在Unreal Engine（UE）中，这些宏定义是用于创建Slate画刷的快捷方式，Slate是UE4的可视化系统。它们被用来在编辑器中创建UI元素，例如按钮、菜单等。下面是每个宏定义的解释：
1. `IMAGE_BRUSH`: 这个宏定义用于创建一个图像画刷，它会在编辑器中使用。`FSlateImageBrush`是一个用于绘制图像的Slate画刷类。`FPaths::EngineContentDir()`用于获取UE引擎的内容目录，而` RelativePath + TEXT(".png")`则是指定图像的相对路径以及文件扩展名。
2. `BOX_BRUSH`: 这个宏定义用于创建一个方形容器画刷，同样用于编辑器中的UI元素。`FSlateBoxBrush`是用于绘制矩形框的Slate画刷类。
3. `BORDER_BRUSH`: 这个宏定义用于创建一个边框画刷，也用于编辑器中的UI元素。`FSlateBorderBrush`是用于绘制边框的Slate画刷类。
4. `GAME_IMAGE_BRUSH`: 这个宏定义用于创建一个游戏图像画刷，它在游戏运行时使用。`FPaths::ProjectContentDir()`用于获取项目的Content目录。
5. `GAME_IMAGE_BRUSH_SVG`: 这个宏定义用于创建一个游戏图像画刷，它使用SVG格式的图像，在游戏运行时使用。
这些宏定义简化了创建Slate画刷的过程，使得开发者可以更方便地使用图像、方形容器或边框等元素来构建UI。
*/