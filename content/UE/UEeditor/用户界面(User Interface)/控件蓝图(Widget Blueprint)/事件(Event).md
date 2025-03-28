-> Event Reply
Capture Mouse 捕获鼠标，用于锁定某个Widget，调用后将只能和锁定的Widget进行响应，该Widget的父类与子类同样无法响应。
Clear User Focus 清空用户焦点
Handled 表示这个事件已经处理完成，如果输出是handled，那么执行完某段事件后输入就会从输入流中移除。比如，UI下一级还有一层子UI，它就接受不到这个按键事件，上图示例中，执行完print string的操作后，该输入就会被移除。
Lock Mouse 锁定鼠标
Release Mouse Capture 释放鼠标捕获
Set Mouse Position 设置鼠标位置
Set User Focus 设置用户焦点
Unhandled 执行完某段事件后输入会从输入流中继续向下流动，如果是在3.中的例子，UI下一级的子UI依旧能接收到该输入。
Unlock Mouse 解锁定鼠标



-> Button Event
On Clicked 点击事件
On Pressed 按下事件
On Released 释放事件
On Hovered 悬停事件
Ön Unhovered 悬停结束事件
->
注意Pressed控件和Clicked控件的差异
Clicked操作实际包含了Pressed的操作，点击按钮时，屏幕同时打印了Clicked和Pressed；
另外长按鼠标时屏幕会打印Pressed，如果此时在Button的范围内松开鼠标左键，则依旧会打印Clicked，如果在Button范围外松开，则仅打印Pressed