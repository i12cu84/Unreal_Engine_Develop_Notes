打开指定关卡,会销毁当前的World,加载一个全新的Level作为World
注:加载新关卡时会有空档期,此时会黑屏
Open Level 会销毁当前的 World，加载一个全新的 Level 作为 World。
在这个 销毁-加载 的过程中，会出现一个空档期：原 World 中所有 Actor 都不复存在，而新 World 的 Actor 还没部署就位，无法运行。
此时会造成加载中的黑屏。

若使用Open Level(by Name),可以从Get Current Level Name节点的Return Value中获取

java的游戏项目的话,不可避免会想到我的世界
