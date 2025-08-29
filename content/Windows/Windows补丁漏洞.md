掉盘bug
```
设置 -> 更新和安全 -> Windows更新 -> 查看更新历史记录

目前明确涉及的系统版本
Windows 11:
24H2 KB5063878 (26100.4946)
23H2 KB5063875 (22621.5768 & 22631.5768)

Windows 10:
22H2 & 21H2 KB5063709 (19044.6216 & 19045.6216)
1809 KB5063877 (17763.7678)
1607 KB5063871 (14393.8330)
TH1 KB5063889 (10240.21100)

漏洞补丁编号(需要卸载!)
Win11：KB5063878
Win10：KB5063709


故障触发:
如SSD使用率超过60%，并连续写入超过50GB数据（DRAM，带缓存式SSD），或更少量的数据（HMB非缓存式SSD）,则会导致此SSD在系统中丢失，重启后可被识别或访问，但再次进行大容量连续写入时故障会复现。
某些SSD会引发更严重的故障，分区会被识别为RAW，磁盘处于锁定状态，无法格式化，无法恢复数据，S.M.A.R.T信息无法读取。即使进入WinPE或更换Linux系统，也无法对磁盘分区进行操作，I/O错误，硬件损坏。
涉及的SSD品牌/所搭载的主控:
群联 Phison PS5012-E12
英韧 InnoGrit
联芸 Maxio
铠侠 Kioxia
闪迪 SanDisk
西数 West Digital
SK海力士 SK Hynix

未明确涉及的品牌及主控:
希捷 Seagate
三星 SAMSUNG
思德 Solidigm
慧荣 SMI
```
cmd指令也可访问:
```
wmic qfe list | findstr "5063709"
```

设置 -> 更新和安全 -> Windows更新 -> 查看更新历史记录 -> 卸载更新 -> 找到目标 -> 右键卸载

-> 暂缓更新方案

按 Win + X 键选择 Windows PowerShell (管理员)

按右键粘贴这行代码后回车即可：
```
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings" /v FlightSettingsMaxPauseDays /t reg_dword /d 10000 /f
```

之后你就可以在 Windows 更新设置——高级选项里面，选择暂停到10000天后更新了

