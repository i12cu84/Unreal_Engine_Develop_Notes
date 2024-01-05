# Unreal Engine Blue Prints Library Node

[中文说明](https://github.com/i12cu84/Blueprint-Function-Libraries-from-mine/blob/main/README(chin).md)

static bool SaveConstraintArray(FString SaveDirectory, FString Filename, TArray<FString> SaveText, bool AllowOverWriting);

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


static FString GetFileNameFromPath(const FString & FilePath);

    Function:

    Gets the filename from the file path

    Input:

    FString FilePath: The path to the file

    Output:

    FString: Filename


static UTexture2D* LoadImageByAbsolutePath(const FString& AbsolutePath);

    Function:

    Get the texture (image) from the engine path and create the returned object

    Input:

    FString AbsolutePath: The path to the file

    Output:

    UTexture2D: Texture object pointer


static UTexture2D* LoadImageFromAbsolutePath(const FString& AbsolutePath);

    Function:

    Get the texture (image) from the file path and create the returned object

    Input:

    FString AbsolutePath: The path to the file

    Output:

    UTexture2D: Texture object pointer


static UMediaSource* LoadMediaSourceFromAbsolutePath(const FString& AbsolutePath);

    Function:

    Get the media source (video) from the file path and create the returned object

    Input:

    FString AbsolutePath: The path to the file

    Output:

    UTexture2D: Media source object pointer