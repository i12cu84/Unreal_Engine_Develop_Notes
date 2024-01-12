; 激活状态变量
active := false

; 激活脚本
^1:: ; 当按下 Alt+1 时
{
    if (active) {
        active := false
        MsgBox, 脚本已取消激活
    } else {
        active := true
        MsgBox, 脚本已激活
    }
}

; 如果脚本激活了，则运行您想要自动化的任务
#IfWinActive ahk_class #32770 ; 假设这是您想要控制的窗口类名
#If active
; 在这里编写您想要自动执行的任务
; 例如，自动点击或输入文本等
; #ClickMouse, 100, 200 ; 点击鼠标
; Send, 您想要自动输入的文本{Enter} ; 发送按键
#If
#IfWinActive ; 结束窗口类名检查
