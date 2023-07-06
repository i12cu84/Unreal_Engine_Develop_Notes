1. UE4日志级别设置
1.1. 日志级别分类
Fatal

Fatal等级日志总是会打印到控制台和日志文件以及crash文件中，甚至logging功能被禁用。

Error

Error等级日志被打印到控制台和日志文件中，默认以红色显示。

Warning

Warning等级日志被打印到控制台和日志文件中，默认以黄色显示。

Display

Display等级日志被打印到控制台和日志文件中。

Log

Log等级日志打印到日志文件中但是不出现在game模式的控制台中，但是通过编辑器的日志输出窗口还是能够被看到。

Verbose

Verbose等级日志打印到日志文件中但是不出现在game模式的控制台中，这个通常被用来作为详细日志和调试使用。

VeryVerbose

VeryVerbose等级日志被打印到日志文件中但是不出现在game模式的控制台中，这通常用来打印非常详细的日志记录否则会产生很多不必要的垃圾输出。

每个日志等级详细程度被四个部分控制：Compile-time verbosity（编译时详细程度）, default verbosity（默认详细程度）, ini verbosity（ini配置详细程度）, runtime-verbosity（运行时详细程度）.

启动时，默认的编译时详细程度被ini配置详细程度覆盖，ini配置被命令行覆盖。

具体配置和命令见下面的各个说明。

1.2. Log conventions (in the console, ini files, or environment variables)
[cat] = a category for the command to operate on, or 'global' for all categories.
[level] = verbosity level, one of: none, error, warning, display, log, verbose, all, default
At boot time, compiled in default is overridden by ini files setting, which is overridden by command line

1.3. Log console command usage
Log list - list all log categories
Log list [string] - list all log categories containing a substring
Log reset - reset all log categories to their boot-time default
Log [cat] - toggle the display of the category [cat]
Log [cat] off - disable display of the category [cat]
Log [cat] on - resume display of the category [cat]
Log [cat] [level] - set the verbosity level of the category [cat]
Log [cat] break - toggle the debug break on display of the category [cat]
1.4. Log command line
-LogCmds=\"[arguments],[arguments]...\"           - applies a list of console commands at boot time
-LogCmds=\"foo verbose, bar off\"         - turns on the foo category and turns off the bar category
1.5. Environment variables
Any command line option can be set via the environment variable UE-CmdLineArgs

set UE-CmdLineArgs=\"-LogCmds=foo verbose breakon, bar off\"
1.6. Config file
In DefaultEngine.ini or Engine.ini:

[Core.Log]
global=[default verbosity for things not listed later]
[cat]=[level]
foo=verbose break
对于不同的系统，你可以设置不同的默认等级，这样可以在调试的时候，将某个类型的某些等级的日志打开，方便调试，正常的情况下默认关闭这些日志等级的输出。具体代码示例如下：

  //显示所有日志语句。
 DECLARE_LOG_CATEGORY_EXTERN （ LogMyGameSomeSystem ， Log ， All ）;

 //不会显示VeryVerbose语句。
 DECLARE_LOG_CATEGORY_EXTERN （ LogMyGameSomeSystem ， Verbose ， All ）;

 //不会显示VeryVerbose和Verbose语句。
 DECLARE_LOG_CATEGORY_EXTERN （ LogMyGameSomeSystem ， VeryVerbose ， All ）;
每个游戏可以根据需要对不同系统创建不同类型的日志，这样方便调试的时候打开某些系统的某些等级的日志，以方便定位问题。

参考链接：

https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime

https://answers.unrealengine.com/questions/78413/ue-log-not-changing-logging-level.html
