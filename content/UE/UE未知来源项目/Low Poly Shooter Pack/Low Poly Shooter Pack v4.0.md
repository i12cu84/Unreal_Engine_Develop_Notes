UE4虚幻 最新版卡通射击游戏项目模板Low Poly Shooter Pack v4.0

更新内容:
加入了开局UI,能够进入单人场景也能开启联机模式

更多不做赘述(已在v3.0中介绍)

环境UE 5.1(必须),可升级到5.2

1.启动的时候缺少Low Poly Core插件(仅支持4.26-4.27,5.0-5.1)

ps:该插件无法在Fab中搜寻到,需要去Epic Game中获取
[下载](https:|www.unrealengine.com/marketplace/zh-CN/product/low-poly-core)

下载后.添加到UE5.1引擎中,插件将会安装到UE5.1的文件目录中

打开项目之后在项目设置中启用LowPolyCore插件之后即可使用

---

2.想将项目升级5.2及以后版本

该插件没有5.2以及后续版本,需要自己修改

笔者方式是将5.1版本插件中的LowPolyCore.h文件复制到项目路径中,启用时会自动载入插件,再使用5.2以上引擎打开即可

参考路径:C:\Program Files\Epic Games\UE_5.1\Engine\Plugins\Marketplace\LowPolyCore

将文件夹LowPolyCore复制到项目路径的Plugins文件夹中

右键.uproject文件 -> Select Unreal Engine Version 自行选择版本

---

操作方式
| 英文                                            | 中文                                     |
| ----------------------------------------------- | ---------------------------------------- |
| **MOVEMENT**↘                                   | 移动控制                                 |
| USE MOUSE TO LOOK AROUND                        | 使用鼠标环顾四周                         |
| USE WASD KEYS TO WALK                           | 使用WASD键移动行走                       |
| HOLD SHIFT TO RUN                               | 按住Shift键奔跑                          |
| PRESS SPACEBAR TO JUMP                          | 按下空格键跳跃                           |
| PRESS LEFT CTRL/C TO CROUCH                     | 按下左Ctrl/C键蹲下                       |
| PRESS Q/E TO LEAN                               | 按下Q/E键侧身倾斜 (**新增**)             |
| **WEAPON**↘                                     | 武器操作                                 |
| PRESS LEFT CLICK TO SHOOT                       | 按下鼠标左键射击                         |
| HOLD RIGHT CLICK TO AIM                         | 按住鼠标右键瞄准                         |
| PRESS R TO RELOAD                               | 按下R键换弹                              |
| PRESS T TO INSPECT                              | 按下T键检视武器 (**新增**)               |
| PRESS 3 TO HOLSTER WEAPON                       | 按下3键收起武器（**调整**旧版为T键）     |
| PRESS H TO LOWER WEAPON                         | 按下H键垂下武器（**调整**旧版为T键）     |
| PRESS Z TO DROP WEAPON                          | 按下Z键丢弃武器                          |
| PRESS 1,2/SCROLLWHEEL TO CYCLE EQUIPPED WEAPONS | 按1/2键或滚轮切换已装备武器              |
| **MELEE**↘                                      | 近战攻击                                 |
| PRESS V TO USE KNIFE ATTACK                     | 按下V键使用匕首攻击（**调整**旧版为F键） |
| **THIRD PERSON**↘                                   | 视角切换                                 |
| PRESS Y TO TOGGLE THIRD-PERSON                  | 按下Y键切换第三人称视角 (**新增**)       |
| **GRENADE**↘                                    | 投掷物                                   |
| PRESS G TO THROW A GRENADE                      | 按下G键投掷手榴弹                        |
| **ATTACHMENTS (IF EQUIPPED)**↘                  | 配件功能（若已装备）                     |
| PRESS X TO RANDOMIZE ATTACHMENTS                | 按下X键随机更换配件 (**新增**)           |
| PRESS J TO TOGGLE LASER/FLASHLIGHT ON/OFF       | 按下J键切换激光/手电筒开关               |
| **PAUSEMENU**↘                                  | 暂停菜单                                 |
| PRESS ESCAPE/P TO PAUSE THE GAME                | 按下ESC/P键暂停游戏                      |
| **TIMESCALE**↘                                  | 时间流速控制                             |
| PRESS 5 TO FREEZE/UNFREEZE TIME                 | 按下5键冻结/解除冻结时间                 |
| PRESS 8 TO DECREASE TIMESCALE                   | 按下8键降低时间流速                      |
| PRESS 9 TO INCREASE TIMESCALE                   | 按下9键加快时间流速                      |