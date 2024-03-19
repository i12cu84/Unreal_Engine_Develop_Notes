https://www.bilibili.com/video/BV1vJ411a7Jc
project.Build.cs
加入"Python"模块

-> .h
static void ExecutePythonScript(FString PythonScript);

-> .cpp
[head file] PythonScriptPlugin.h
void [class]::ExecutePythonScript(FString PythonScript)
{
    FPythonScriptPlugin::Get()->ExecPythonCommand(*PythonScript);
}