此模板具有酷炫低多边形风格的高级射击游戏包，专注于抛光机制和高质量动画，可用作游戏项目、原型设计或学习的起点。以下是该模板的主要特征以及相关信息：

主要特征：
240 多种武器材料
170+ 种角色素材
游戏UI图标和 HUD
视觉特效
50 多种武器预设
多种附件类型
第一人称和第三人称角色模型
包括动画

引擎版本:
4.26(4.27也能直接打开),商店显示5.0~5.1也兼容

---

1.源代码4.27提升引擎到5.2.1的时候运行出现问题
经过c++工程编译(蓝图转c++工程流程不赘述),发现是插件源代码问题

文件路径:项目路径->Plugins->LowPolyCore->Source->LowPolyShooterPack->Private->LPSPExplosionComponent.cpp

```cpp
//65行
if(!Result.Actor.Get()->CanBeDamaged())
//69行
ALPSPDamageable* Damageable = Cast<ALPSPDamageable>(Result.Actor.Get());
```
修改为
```cpp
//65行
if(!Result.GetActor()->CanBeDamaged())
//69行
ALPSPDamageable* Damageable = Cast<ALPSPDamageable>(Result.GetActor());
```
即可

原因分析:Unreal Engine 5+ 中，FHitResult的Actor成员被封装为方法GetActor()，以提高安全性和兼容性。直接访问成员变量的旧代码需要适配新的API。

```cpp
ALPSPDamageable* Damageable = Cast<ALPSPDamageable>(Result.Actor.Get());
```
Result.Actor 的类型：旧版本中 FHitResult::Actor 是 TWeakObjectPtr<AActor> 类型。

TWeakObjectPtr 是一个弱引用指针，不会阻止目标对象被垃圾回收。

必须通过 .Get() 方法获取原始指针 AActor*，但存在对象已被销毁的风险（返回 nullptr）。

```cpp
ALPPDamageable* Damageable = Cast<ALPSPDamageable>(Result.GetActor());
```
Result.GetActor() 的返回类型：直接返回 AActor*。

在 UE5+ 中，FHitResult 可能不再通过 TWeakObjectPtr 存储 Actor 引用，而是通过其他机制（如直接存储原始指针或更安全的智能指针）。

GetActor() 方法内部可能封装了更健壮的对象有效性检查，减少悬垂指针风险。

旧代码的问题：
```
直接访问 FHitResult 内部成员 Actor：违反面向对象设计的封装原则。

依赖具体实现细节：如果引擎内部将 Actor 成员改为其他存储方式（如 TSharedPtr 或新的智能指针），旧代码会直接因成员不存在而编译失败。
```
新代码的优势：
```
调用接口方法 GetActor()：

隐藏底层实现细节，仅暴露接口。

引擎团队可以在 GetActor() 内部自由升级存储机制（例如改用 TObjectPtr），而无需开发者修改代码。

通过接口方法可能实现额外的安全性检查（如断言或空指针过滤）。
```

假设旧代码的潜在风险：
```cpp
// 若 Result.Actor 是 TWeakObjectPtr，且目标 Actor 已被销毁
AActor* RawActor = Result.Actor.Get(); // 可能返回 nullptr
ALPSPDamageable* Damageable = Cast<ALPSPDamageable>(RawActor); // 可能崩溃
```
新代码的改进：
```cpp
// GetActor() 可能包含内部有效性检查
AActor* RawActor = Result.GetActor(); // 引擎可能已处理对象有效性
ALPSPDamageable* Damageable = Cast<ALPSPDamageable>(RawActor); // 更安全
```

---


操作方式
| 英文                                              | 中文                                 |
| ------------------------------------------------- | ------------------------------------ |
| Controls                                          | 控制设置                             |
| Movement                                          | 移动控制                             |
| Mouse to look around                              | 使用鼠标环顾四周                     |
| WASD keys to walk.                                | 使用WASD键移动                       |
| Left shift (hold) to run.                         | 按住左Shift键奔跑                    |
| Space bar to jump.                                | 按下空格键跳跃                       |
| Left Ctrl/C key to crouch.                        | 按下左Ctrl/C键蹲下                   |
| Weapon                                            | 武器操作                             |
| Left click to shoot.                              | 按下鼠标左键射击                     |
| Right click (hold) to aim.                        | 按住鼠标右键瞄准                     |
| R key to reload.                                  | 按下R键换弹                          |
| T key to inspect weapon.                          | 按下T键检视武器                      |
| -H key to holster, and H again to take out weapon | 按下H键收起武器，再次按H取出武器     |
| Z key to drop weapon.                             | 按下Z键丢弃武器                      |
| Scrollwheel key to cycle equipped weapons.        | 使用滚轮切换已装备武器               |
| Melee                                             | 近战攻击                             |
| F key to use knife attack                         | 按下F键使用匕首攻击                  |
| Grenade                                           | 投掷物                               |
| G key to throw a grenade.                         | 按下G键投掷手榴弹                    |
| Attachments (if enabled)                          | 配件功能（若已启用）                 |
| J key to toggle on/off.                           | 按下J键切换配件开关（如激光/手电筒） |
| Pause Menu                                        | 暂停菜单                             |
| Escape/P key to pause and show options menu.      | 按下ESC/P键暂停并显示选项菜单        |
| Timescale                                         | 时间流速控制                         |
| 5 key to freeze/unfreeze time                     | 按下5键冻结/解除冻结时间             |
| 8 key to decrease timescale                       | 按下8键降低时间流速                  |
| 9 key to increase timescale                       | 按下9键加快时间流速                  |

