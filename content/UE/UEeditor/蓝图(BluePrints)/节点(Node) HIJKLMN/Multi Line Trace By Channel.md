将沿给定线条执行碰撞追踪，并返回所有遭遇的命中，直到并包含首次阻挡命中，只返回对指定追踪通道响应的对象。这意味着（实际上讲），如果追踪的开始和结束之间有多个带碰撞的 Actor 或 组件（Component） 与指定追踪通道发生 重叠（Overlap） ，你将接收到所有这些Actor和组件。但如果首次命中 阻挡（Block） 了指定追踪通道，则你只会接收到这一个项目。如果你希望无视追踪通道的重叠或阻挡接收到所有项目，则应使用Multi Line Trace By Object节点

参考文献
https://docs.unrealengine.com/5.0/zh-CN/using-a-multi-line-trace-raycast-by-channel-in-unreal-engine/