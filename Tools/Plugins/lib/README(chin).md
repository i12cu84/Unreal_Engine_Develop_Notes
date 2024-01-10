# Unreal Engine Blue Prints Library Node
	
static bool SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString> SaveText, bool AllowOverWriting);

	Function:

		导出数组数据保存到本地

	Input:

		FString SaveDirectory		:保存到目标路径

		FString Filename			:设定导出csv文件的名字

		TArray<FString> SaveText	:存储内容,以","隔开为列,以数组索引为行

		bool AllowOverWriting		:是否覆盖

	Output:

		bool ver					:是否导出成功


static TArray<FString> LoadConstraintArray(FString FilePath);

	Function:

		导入数组数据到蓝图中

	Input:

		FString FilePath			:读取csv的路径

	Output:

		TArray<FString> ver			:返回csv中的内容


static bool DeleteFile(FString FilePath);

	Function:

		删除指定文件

	Input:

		FString FilePath			:删除目标文件的路径

	Output:

		bool ver					:是否删除成功


static TArray<ULineBatchComponent*> DrawRayLine(FVector StartPos, FVector EndPos, float fLifeTime, FLinearColor color);

	Function:

		绘制一条线

	Input:

		FVector StartPos					:线的三维起点

		FVector EndPos						:线的三维终点

		float fLifeTime						:绘制线存在的时间(推荐0.02s左右)

		FLinearColor color					:绘制线的颜色

	Output:

		TArray<ULineBatchComponent*> ver	:绘制线的对象


static void DestoryLine(TArray<ULineBatchComponent*> LineList);

	Function:

		清空线对象的对象

	Input:

		TArray<ULineBatchComponent*> LineList	:需要清空的线对象


static TArray<FString> GetAllSaveFileNames(const FString& Directory);

	Function:

		获取文件路径下的文件列表

	Input:

		FString Directory					:文件根目录的路径

	Output:

		TArray<FString> ver					:路径下文件对象路径组


static FString GetFileNameFromPath(const FString & FilePath);

	Function:

		从文件路径中获取文件名

	Input:

		FString FilePath					:文件的路径

	Output:

		FString								:文件名


static UTexture2D* LoadImageByAbsolutePath(const FString& AbsolutePath);

	Function:

		从引擎路径中获取纹理(图片)并创建返回的对象

	Input:

		FString AbsolutePath				:文件的路径

	Output:

		UTexture2D							:纹理对象指针


static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath);

	Function:

		从文件路径中获取纹理(图片)并创建返回的对象

	Input:

		FString AbsolutePath				:文件的路径

	Output:

		UTexture2D							:纹理对象指针


static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath);

	Function:

		从文件路径中获取媒体源(视频)并创建返回的对象

	Input:

		FString AbsolutePath				:文件的路径

	Output:

		UTexture2D							:媒体源对象指针