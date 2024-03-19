# Unreal Engine Blue Prints Library Node

<details>
<summary>API parsing (English)</summary>
<pre><code>

static void CopyMessageToClipboard(FString text)
Function:
Overwrite the clipboard contents
Input:
FString text: Copies the content

static FString PasteMessageFromClipboard()
Function:
Gets the clipboard contents
Output:
FString ver: The output

static bool IsValidFilePath(const FString& FilePath)
Function:
Determines if the path is valid
Input:
FString& FilePath: The file path
Output:
bool ver: Whether the path is valid

static TArray<FString> GetFilesInDirectory(const FString& DirectoryPath)
Function:
To get a file with a specified path, you can only get a folder
Input:
FString& DirectoryPath: Folder path
Output:
TArray<FString> ver: path to the folder file

static TArray<FString> GetMP3FilePaths(const FString& Directory)
Function:
Only mp3 files can be retrieved from the specified path
Input:
FString& Directory: Folder path
Output:
TArray<FString> ver: path to the folder file

static FString GetFileNameFromPath(const FString& FilePath)
Function:
Extract the filename from the file path
Input:
FString& FilePath: The file path
Output:
FString ver: Filename

static bool DeleteFileAtPath(const FString& FilePath)
Function:
Deleting files
Input:
FString& FilePath: The file path
Output:
bool ver: Whether the operation was successful

static float SetSUVM()
Function:
UE can play in the background
Output:
float ver: Output 1.0f for background playback,0.0f for non-background playback

static bool SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString> SaveText,  bool AllowOverWriting);
Function:
The exported array data is saved locally
Input:
FString SaveDirectory: Save to the destination path
FString Filename: This specifies the name of the exported csv file
TArray<FString> SaveText: Stores content separated by "," as columns and array index as rows
bool AllowOverWriting: Whether to override
Output:
bool ver: Whether the export was successful

static TArray<FString> LoadConstraintArray(FString FilePath);
Function:
Import the array data into the blueprint
Input:
FString FilePath: The path to read the csv
Output:
TArray<FString> ver: This returns the contents of the csv

static bool DeleteFile(FString FilePath);
Function:
Delete specified file
Input:
FString FilePath: The path to delete the target file
Output:
bool ver: Whether the deletion was successful

static TArray<ULineBatchComponent*> DrawRayLine(FVector StartPos, FVector EndPos, float fLifeTime, FLinearColor color);
Function:
Draw a line
Input:
FVector StartPos: The 3D starting point of the line
FVector EndPos: The 3D end of the line
float fLifeTime: The lifetime of the drawn line (about 0.02s recommended)
FLinearColor color: The color of the drawing line
Output:
TArray<ULineBatchComponent*> ver: The object on which the line is drawn

static void DestoryLine(TArray<ULineBatchComponent*> LineList);
Function:
The object that clears the line object
Input:
TArray<ULineBatchComponent*> LineList: The line object to be cleared

static TArray<FString> GetAllSaveFileNames(const FString& Directory);
Function:
Gets a list of files in the file path
Input:
FString Directory: The path to the root directory of the file
Output:
TArray<FString> ver: File object path group under path

static FString GetFileNamePath(const FString& FilePath)
Function:
Get the texture (image) from the file path and create the returned object
Input:
FString FilePath: The path to the file
Output:
FString: Filename

static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath);
Function:
Get the texture (image) from the file path and create the returned object
Input:
FString AbsolutePath: The path to the file
Output:
UTexture2D: Texture object pointer

static AActor* GetActorByName(TArray<AActor*> Actors, const FString& ActorName)
Function:
Actors are extracted according to UAID
Input:
TArray<AActor*> Actors :Actor search source
FString& ActorName :Actor name (UAID)
Output:
AActor* : The Actor pointer

static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath)
Function:
Getting the media player
Input:
FString& AbsolutePath: The file path
Output:
UMediaSource: The media player pointer

</code></pre>
</details>

<details>
<summary>API 解析(中文)</summary>
<pre><code>

static void CopyMessageToClipboard(FString text)
	Function:
		覆盖剪切板内容
	Input:
		FString text				:复制内容

static FString PasteMessageFromClipboard()
	Function:
		获取剪切板内容
	Output:
		FString ver					:输出内容

static bool IsValidFilePath(const FString& FilePath)
	Function:
		获取路径是否有效
	Input:
		FString& FilePath			:文件路径
	Output:
		bool ver					:路径是否有效

static TArray<FString> GetFilesInDirectory(const FString& DirectoryPath)
	Function:
		获取指定路径的文件 只能获取文件夹
	Input:
		FString& DirectoryPath		:文件夹路径
	Output:
		TArray<FString> ver			:文件夹子文件路径

static TArray<FString> GetMP3FilePaths(const FString& Directory)
	Function:
		获取指定路径的文件 只能获取mp3文件
	Input:
		FString& Directory 			:文件夹路径
	Output:
		TArray<FString> ver			:文件夹子文件路径

static FString GetFileNameFromPath(const FString& FilePath)
	Function:
		从文件路径中提取文件名
	Input:
		FString& FilePath			:文件路径
	Output:
		FString ver					:文件名

static bool DeleteFileAtPath(const FString& FilePath)
	Function:
		删除文件
	Input:
		FString& FilePath			:文件路径
	Output:
		bool ver					:是否操作成功

static float SetSUVM()
	Function:
		UE可后台播放
	Output:
		float ver					:输出1.0f为可后台播放,0.0f为不可后台播放

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

static FString GetFileNamePath(const FString& FilePath)
	Function:
		从文件路径中获取纹理(图片)并创建返回的对象
	Input:
		FString FilePath				:文件的路径
	Output:
		FString							:文件名

static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath);
	Function:
		从文件路径中获取纹理(图片)并创建返回的对象
	Input:
		FString AbsolutePath				:文件的路径
	Output:
		UTexture2D							:纹理对象指针

static AActor* GetActorByName(TArray<AActor*> Actors, const FString& ActorName)
	Function:
		按照UAID提取Actor
	Input:
		TArray<AActor*> Actors				:Actor搜索源
		FString& ActorName					:Actor名字(UAID)
	Output:
		AActor*								:Actor指针

static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath)
	Function:
		获取媒体播放器
	Input:
		FString& AbsolutePath				:文件路径
	Output:
		UMediaSource						:媒体播放器指针

</code></pre>
</details>