关卡蓝图中调用 用于预处理缓存地图(以便后续在Active Level方式激活)

Load Stream Level 不会销毁当前 World，而是将 Level 流送到当前的 World 中，Stream Level 需要在 Level 面板中提前设置。
由于加载过程中 World 是始终存在的，因此能够同时在 Load Stream Level 时运行其它 Actor。
可以通过 Unload Stream Level 卸载 Stream Level。可以很方便地在主关卡中获得 Stream Level Actors 的引用。44