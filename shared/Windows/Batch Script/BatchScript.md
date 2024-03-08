1. 打印当前日期和时间：
echo %date% %time%
2. 显示目录中的所有文件：
dir
3. 创建一个新目录：
mkdir new_directory
4. 删除一个目录及其所有内容：
rmdir /s directory_to_delete
5. 复制一个文件：
copy file_to_copy destination_directory
6. 移动一个文件：
move file_to_move destination_directory
7. 显示系统环境变量：
set
8. 显示当前目录：
cd
9. 显示当前目录中的所有文件和子目录：
dir /s
10. 显示当前目录中的所有文件，按文件大小排序：
dir /o-s
11. 在命令提示符或脚本中输出文本
echo Hello, World!
12. 条件语句，根据条件执行不同的命令。
if %var%==value (
    echo Variable is equal to value
) else (
    echo Variable is not equal to value
)
13. 循环结构，对一系列文件或文本进行迭代处理。
    <details>
    <summary>loop</summary>
    <pre><code>
        for %%G in (*.txt) do (
            echo Processing file: %%G
        )
        BatchScript 的循环语法主要包括 FOR 和 DO 循环。以下是如何使用这些循环语法的详细说明：
        1. FOR 循环
            FOR 循环的基本语法如下：
            ```
            for /l %i in (start, end) do
                command
            ```
            其中，%i 是循环变量，start 和 end 是数字，表示循环的范围。command 是循环体，表示在循环中需要执行的命令。
            示例：求 1 到 10 的和
            ```
            for /l %i in (1, 10) do (
                echo %i
                )
            ```
            输出结果：
            ```
            1
            2
            3
            4
            5
            6
            7
            8
            9
            10
            ```
        2. DO 循环
        DO 循环的基本语法如下：
        ```
        do command
            until /b condition
        ```
        其中，command 是需要循环执行的命令，condition 是循环结束的条件。
        示例：使用 DO 循环实现 1 到 10 的乘法表
        ```
        echo off
        do /b %i in (1, 10) do (
            echo %i*%i=%i
        )
        ```
        输出结果：
        ```
        1*1=1
        1*2=2
        1*3=3
        1*4=4
        1*5=5
        1*6=6
        1*7=7
        1*8=8
        1*9=9
        1*10=10
        ```
        以上就是 BatchScript 中循环语法的使用方法。在实际编写脚本时，可以根据需要灵活运用这些循环语法来完成各种任务。
    </code></pre>
    </details> 
14. 调用另一个批处理文件。
call other_script.bat
15. goto 跳转到脚本中的特定标签。
if %var%==value (
    goto LabelName
)
16. setlocal和endlocal在脚本中创建局部环境变量:它主要针对临时环境变量，不会影响到系统的全局环境设置。使用 setlocal 设置的局部环境变量只在当前批处理文件的作用域内有效，当批处理文件执行完毕后，这些局部环境变量将会被恢复。
setlocal
set LOCAL_VAR=value
...
endlocal
17. rem 添加注释，不会执行。
rem This is a comment
18. 暂停脚本的执行，等待用户按下任意键继续。
pause
19. 注释
REN xxxx
20. 声明
set xxx=xxx
21. 关闭回显
@echo off
22. 开启变量延迟扩展
setlocal enabledelayedexpansion 是批处理（Batch）文件中的一种命令，用于开启变量延迟扩展（Delayed Expansion）功能。当使用此命令后，批处理脚本中的变量会在脚本运行过程中动态地更新，而不是在脚本开始执行时立即赋值。
21. 执行另一个批处理文件或外部程序
当 call 命令被执行时，它会暂停当前批处理文件的执行并执行指定的程序或批处理文件。
    在批处理文件中，你可以使用以下语法来使用 call 命令：
    call [parameters] [program] [parameters]
    其中，[program] 是你想要执行的程序或批处理文件的路径，而 [parameters] 是传递给该程序或批处理文件的参数。
    例如，假设你有一个名为 example.bat 的批处理文件，其中包含以下内容：
    @echo off
    echo Hello, World!
    call myprogram.exe
    echo This is the end of the script.
    在这个例子中，call myprogram.exe 表示执行名为 myprogram.exe 的外部程序。当 example.bat 被运行时，它会首先输出 “Hello, World!”，然后执行 myprogram.exe，最后输出 “This is the end of the script.”。
    需要注意的是，在调用外部程序或批处理文件时，当前批处理文件中的任何后续命令都不会在 call 命令执行完毕后执行，除非在 call 命令后面使用 :: 来标记一个标签，以便在 call 命令执行完毕后返回到该标签所在的位置继续执行。



-----------------------------------------------------------------------------------------------------------------------------------------------------------

 Batch Script，即批处理脚本，是Windows操作系统中使用的一种脚本语言，它允许用户通过编写一段简单的文本脚本来自动执行一系列的操作。批处理脚本通常用于自动化日常任务，如文件管理、系统配置等。
以下是一个基本的批处理脚本使用方法介绍：
1. **创建批处理文件**：
   - 打开记事本或其他文本编辑器。
   - 编写脚本命令。
   - 保存文件时，选择文件类型为“所有文件（*.*)”，并给文件一个扩展名“.bat”，例如“example.bat”。
2. **运行批处理文件**：
   - 双击桌面上的批处理文件或通过命令行运行。
   - 如果是通过命令行运行，需要在命令前加上“@”符号，例如：“@example.bat”。
3. **脚本命令示例**：
   - `@echo off`：关闭命令回显，使输出更加清晰。
   - `echo`：在屏幕上显示文本信息。
   - `set`：设置环境变量。
   - `cd`：改变当前目录。
   - `copy`：复制文件。
   - `del`：删除文件。
   - `move`：移动文件。
   - `mkdir`：创建新目录。
   - `rmdir`：删除目录。
   - `start`：启动一个程序。
4. **常见的批处理任务**：
   - 文件复制：`copy /Y source.txt dest.txt`，将source.txt文件复制到dest.txt。
   - 文件删除：`del /F /Q files.txt`，删除名为files.txt的文件。
   - 创建新文件夹：`mkdir new_folder`，创建名为new_folder的新文件夹。
   - 移动文件：`move /Y source.txt dest_folder`，将source.txt文件移动到dest_folder目录下。
5. **脚本示例**：
   ```batch
   @echo off
   setlocal EnableDelayedExpansion
   set "folder=C:\My Documents"
   set "file=myfile.txt"
   cd /d "%folder%"
   if not exist "%file%" (
       echo File not found.
   ) else (
       copy /Y "%file%" "backup.txt"
       echo File has been backed up.
   )
   endif
   endlocal
   ```
这个脚本会检查指定文件夹中是否存在一个名为myfile.txt的文件，如果不存在，它会显示一条消息；如果存在，它会将该文件复制一份并重命名为backup.txt。
使用批处理脚本时，请确保你理解每个命令的作用，并谨慎操作，因为错误的命令可能会对系统造成损害。不建议初学者执行高级操作，应在有经验的用户指导下进行。同时，涉及到系统配置和高级操作时，建议备份相关数据，以防不测。