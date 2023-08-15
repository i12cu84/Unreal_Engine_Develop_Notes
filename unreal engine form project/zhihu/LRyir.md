
<details>
<summary>UE4 小地图和一些Indicator的实现思路</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/130483785首先
小地图在游戏里是很重要的一部分（虽然没有也可以），这篇文章我会用最短的时间里用
UMG蓝图做出一个能显示位置的小地图出来，
先上实现效果
动图封面
gif
超级简单 对吧
红色的点是玩家的位置，白点代表目标的位置（图中是桌子）思路基本就是把目标物体的世界坐标转换到我们玩家的本地坐标，然后在 Widget 里更新一下位置显示出来就行了
下面开始--------------
Widget Blueprint
首先是一个 Canvas 容器里面放两个 Image 代表玩家和目标
widget
需要注意的是两个 image 的 Align（Anchors设置） 一定要放到中间 （本地坐标）
设置好了之后就可以直接在 Tick 里给我们的 Target image 的 Position 赋值了（Player 不
需要管毕竟就是一个装饰方便我们观察）
不能直接 Set Position
接下来我们在来求出这个 Positon.
Transform
接下来就需要空间坐标转换了， Kismet 里有现成的蓝图节点我们可以直接使用。
首先用 Inverse Transform Location 把一个世界位置的向量转换成一个物体的本地坐标的向量。变换完了之后呢，我们不需要 z 轴只需要 x 和 y，其实直接把这个 x 和 y 赋值就可以看到效果了，但是我们还得乘一下这个 DPI Scale（1/Viewport Scale） 这东西是给多平台 UI 做缩放用的，我也不太了解，具体内容去 docs 自己看看吧，后面的除呢，就相当于放大和缩小地图了，否则这个 image 很容易就跑到屏幕外边去了（下面解决）.
bp
Rotation 的 Yaw 加了 90 是为了旋转一下地图.
Clamp
最后就是我们要限制一下这个得到的 Position 不能让它跑到外面去（因为一般大家都是这样做的）
很简单 我们只需要限制一下 Position 的 x 和 y 就行了限制的多少根据你 UI 的大小来决定。
clamp
不过这不是重点，上面实现了一个方形地图，如果我们的项目要求一个圆形的小地图呢，你这么直接 clamp 出一个矩形区域是肯定不行的，那圆形限制区域要怎么实现呢？
CIRCLEKING
我们需要转换一下思路，别直接把矩阵转换出来位置向量直接赋值，而是把他 normalize （标准化）一下求出一个方向向量来（这么说其实不太严谨），再拿这个方向乘以它标准化之前的长度，在赋值之前限制一下它的长度就OK了
圆形限制
以上就是 mini map 的一个实现思路，
</code></pre>
</details>

<details>

<summary>UE4 里的 Camera 系统</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/149176416
UE4 通过 APlayerCameraManager 里的 ViewTarget 变量来定义渲染屏幕的摄像机
它的类型是一个结构体 FTViewTarget (APlayerCameraManager.h 60行)
里面有两个重要的属性， AActor 和 FMinimalViewInfo(里面是摄像机数据)
/** A ViewTarget is the primary actor the camera is associated with. */
USTRUCT(BlueprintType)
struct ENGINE_API FTViewTarget
{
	GENERATED_USTRUCT_BODY()
public:
	/** Target Actor used to compute POV */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TViewTarget)
	class AActor* Target;
	/** Computed point of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TViewTarget)
	struct FMinimalViewInfo POV;
PlayerCameraManager 通过 ViewTarget 里的 AActor* Target 获取摄像机的信息
使用 APlayerCameraManager::SetViewTarget() 可以设置这个 Actor
蓝图用 PayerController 设置
AActor.h 下有一个 CalcCamera 的虚函数，重写它就能设置当这个 Actor 作为 ViewTarget 时的 Camera 的数据(FMinimalViewInfo)
函数声明 通过引用返回一个 FMinimalViewInfo
先看一看 .cpp 里 CalcCamera 的实现：从所有组件里找到一个可用的 CameraComponent 然后把它的数据(location rotation FOV之类) 返回出去 赋值给我们的 ViewTarget，如果找不到的话就用 GetActorEyesViewPoint 里得到的位置和旋转赋值给 ViewTarget
cpp文件下的默认实现
下面是 PlayerCameraManager 用 CalcCamera 来更新 ViewTarget
void APlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	if (OutVT.Target)
	{
		FVector OutLocation;
		FRotator OutRotation;
		float OutFOV;
		if (BlueprintUpdateCamera(OutVT.Target, OutLocation, OutRotation, OutFOV))
		{
			OutVT.POV.Location = OutLocation;
			OutVT.POV.Rotation = OutRotation;
			OutVT.POV.FOV = OutFOV;
		}
		else
		{
			OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
		}
	}
}
BlueprintUpdateCamera 是给蓝图用的，可以在PlayerCameraManager 的蓝图里重写。
PlayerCameraManager 里的 ViewTarget 下面两个属性 FMinimalViewInfo 和一个 AActor 的指针，FMinimalViewInfo 就是你的摄像机，里面有相机用到的所有数据。那个 Actor 就是用来更新 FMinimalViewInfo 给它赋值用的，通过它的虚函数 CalcCamera。 所以所有 Actor 都可以拿来当摄像机用，也就是为什么用 PlayerController 设置 ViewTarget 需要一个 Actor 而不是一个 CameraComponent
</code></pre>
</details>

<details>
<summary>UE4 Procedural Mesh 程序化模型</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/346745928
ue4 用 Procedural Mesh Component 调用 CreateMeshSection 可以生成模型
Vertices 是这个模型的所有顶点，下面的 Normal 法线向量、UV 贴图坐标、VertexColor 顶点颜色、Tangent 切线方向，都是和顶点对应的，但是 Triangles 这个整数数组比较特殊，它表示的是这个模型所有的面。比如说一个矩形平面有四个顶点，你还需要用这四个顶点连出来两个三角面，模型才能显示，Triangles 用 Vertices 的数组下标连线，每个三角面可以顺时针连和逆时针连，区别就在于面的朝向。
用三个数组下标连一个三角面，两个三角面分别是 0 2 1 和 1 2 3
用 Procedural Mesh 可以生成一些简单的面片做特效很有用
动图封面
生成地形 ------------------------------
代码：
// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyActor.generated.h"
UCLASS()
class DOORROOMS_API AMyActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AMyActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 网格大小
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Generate")
	FVector2D GridSize = FVector2D(100, 100);
	// X 轴顶点数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Generate")
	int32 Length = 10;
	// Y 轴顶点数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Generate")
	int32 Width = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	int32 NoiseSeed = 7777;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseScale = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.00001", UIMax = "0.1"), Category = "Noise")
	float NoiseFactor = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProceduralMeshComponent* Mesh;
	UFUNCTION(BlueprintCallable)
	void GenerateMesh();
	UFUNCTION()
	void GenerateGrid(TArray<FVector>& InVertices, TArray<int32>& InTriangles, TArray<FVector>& InNormals, TArray<FVector2D>& InUV0, TArray<FColor>& InVertexColor, TArray<float>InNoiseHeight, FVector2D InSize, int32 InLength, int32 InWidth);
private:
	void GetHeights(TArray<float>& InHeights);
};
// Fill out your copyright notice in the Description page of Project Settings.
#include "MyActor.h"
#include "SimplexNoiseBPLibrary.h"
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
}
// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMyActor::GenerateMesh()
{
	if (GridSize.X <= 0 || GridSize.Y <= 0 || Length < 1 || Width < 1) return;
	Mesh->ClearAllMeshSections();
	// Mesh buffers
	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FColor> vertexColors;
	TArray<float> heights;
	GetHeights(heights);
	GenerateGrid(vertices, triangles, normals, UV0, vertexColors, heights, GridSize, Length, Width);
	Mesh->CreateMeshSection(0,vertices, triangles, normals, UV0, vertexColors, tangents, true);
}
void AMyActor::GenerateGrid(TArray<FVector>& InVertices, TArray<int32>& InTriangles, TArray<FVector>& InNormals, TArray<FVector2D>& InUV0, TArray<FColor>& InVertexColor, TArray<float> InNoiseHeight, FVector2D InSize, int32 InLength, int32 InWidth)
{
	FVector2D SectionSize = FVector2D(InSize.X / InLength, InSize.Y / InWidth);
	int32 VertexIndex = 0;
	for (int X = 0; X < InLength + 1; X++)
	{
		for (int Y = 0; Y < InWidth + 1; Y++)
		{
			float z = VertexIndex < InNoiseHeight.Num() ? InNoiseHeight[VertexIndex] : 0;
			InVertices.Add(FVector(X * SectionSize.X, Y * SectionSize.Y, z * NoiseScale));
			FLinearColor color = FLinearColor(0, 0, 0, z);
			InVertexColor.Add(color.ToFColor(true));
			// UV
			FVector2D uv = FVector2D((float)X / (float)InLength, (float)Y / (float)InWidth);
			InUV0.Add(uv);
			// Once we've created enough verts we can start adding polygons
			if (X > 0 && Y > 0)
			{
				int32 bTopRightIndex = (X * (InWidth + 1)) + Y;
				int32 bTopLeftIndex = bTopRightIndex - 1;
				int32 pBottomRightIndex = ((X - 1) * (InWidth + 1)) + Y;
				int32 pBottomLeftIndex = pBottomRightIndex - 1;
				// Now create two triangles from those four vertices
				// The order of these (clockwise/counter-clockwise) dictates which way the normal will face. 
				InTriangles.Add(pBottomLeftIndex);
				InTriangles.Add(bTopRightIndex);
				InTriangles.Add(bTopLeftIndex);
				InTriangles.Add(pBottomLeftIndex);
				InTriangles.Add(pBottomRightIndex);
				InTriangles.Add(bTopRightIndex);
			}
			VertexIndex++;
		}
	}
	// normal
	for (int X = 0; X < InLength + 1; X++)
	{
		for (int Y = 0; Y < InWidth + 1; Y++)
		{
			int32 c = (X * (InWidth + 1)) + Y;
			int32 centerUp = c + InWidth + 1;
			int32 centerBottom = c - (InWidth + 1);
			int32 centerRight = c + 1;
			if (centerRight > ((X * (InWidth + 1)) + InWidth))
			{
				centerRight = -1;
			}
			int32 centerLeft = c - 1;
			if (centerLeft < (X * (InWidth + 1)))
			{
				centerLeft = -1;
			}
			int32 centerUpRight = centerUp + 1;
			if (centerUpRight > (X + 1) * (InWidth + 1) + InWidth)
			{
				centerUpRight = -1;
			}
			int32 centerBottomLeft = centerBottom - 1;
			if (centerBottomLeft < (X - 1) * (InWidth + 1))
			{
				centerBottomLeft = -1;
			}
			int32 indexs[6] = { centerUp,centerUpRight,centerRight,centerBottom,centerBottomLeft,centerLeft };
			TArray<FVector> vers;
			// get all the normal of triangles that using the current vertex
			for (int i = 0; i < 6; i++)
			{
				int32 NextIndex = (i + 1 >= 6) ? 0 : (i + 1);
				if (indexs[i] >= 0 && indexs[i] < InVertices.Num() && indexs[NextIndex] >= 0 && indexs[NextIndex] < InVertices.Num())
				{
					FVector a = (InVertices[indexs[i]] - InVertices[c]).GetUnsafeNormal();
					FVector b = (InVertices[indexs[NextIndex]] - InVertices[c]).GetUnsafeNormal();
					vers.Add(FVector::CrossProduct(a, b).GetUnsafeNormal());
					break;
				}
			}
			// get the average Vector
			FVector NormalSum = FVector(0, 0, 1);
			for (auto& i : vers)
			{
				NormalSum += i;
			}
			InNormals.Add(NormalSum / vers.Num());
		}
	}
}
void AMyActor::GetHeights(TArray<float>& InHeights)
{
	if (NoiseScale == 0) return;
	USimplexNoiseBPLibrary::setNoiseSeed(NoiseSeed);
	for (auto X = 0; X < Length + 1; X++)
	{
		for (auto Y = 0; Y < Width + 1; Y++)
		{
			InHeights.Add(USimplexNoiseBPLibrary::SimplexNoise2D(X, Y, NoiseFactor));
		}
	}
}
生成高度图的插件
https://github.com/devdad/SimplexNoise
​github.com/devdad/SimplexNoise
在 c++ 里使用插件
https://ue4community.wiki/legacy/procedural-mesh-component-in-cpp:getting-started
​ue4community.wiki/legacy/procedural-mesh-componen
</code></pre>
</details>