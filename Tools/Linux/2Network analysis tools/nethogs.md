 nethogs 是一个简单易用的网络带宽监控工具，它可以显示系统中每个网络接口的实时带宽使用情况。nethogs 将每个接口的带宽使用情况以 Hog 单位（1 Hog = 1000000 bytes/s）进行显示，方便用户了解各个接口的流量状况。
在 Linux 系统中，可以使用以下命令安装 nethogs：
```
sudo apt-get install nethogs
```
或者
```
sudo yum install nethogs
```
安装完成后，可以直接运行 nethogs 命令来查看网络带宽使用情况。默认情况下，nethogs 显示所有网络接口的带宽使用情况。如果需要查看特定接口的带宽使用情况，可以使用以下命令：
```
nethogs -i eth0
```
其中，`-i` 表示指定网卡接口。
此外，nethogs 还支持一些其他参数，如 `-h`（显示历史带宽使用情况）、`-l`（显示已建立的连接数）等。具体使用方法可以参考 nethogs 的官方文档或相关教程。