不会销毁当前的World,将另一个Level Instance添加到当前的World
加载过程中World是始终存在的,因此能够同时在Load Level Instance时运行其他Actor
注:可以通过Set is Requesting Unload and Removal 卸载 Level Instance

Load Level Instance 不会销毁当前的 World，而是将另一个 Level Instance 添加到当前的 World 中，
由于加载过程中 World 是始终存在的，因此能够同时在 Load Level Instance 时运行其它 Actor。
可以通过 Set is Requesting Unload and Removal 卸载 Level Instance。