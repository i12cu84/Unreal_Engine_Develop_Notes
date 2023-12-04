 iftop是一款用于监控Linux系统中网络流量的工具，它可以实时显示网络接口的流量情况。类似于top命令，iftop以流量使用情况为依据，对网络接口进行排序，方便用户了解各个接口的流量状况。iftop广泛应用于网络故障排查、网络性能优化等场景。
要使用iftop，首先需要确保已经安装了它。根据参考资料，可以在Linux系统中使用以下命令安装：
1. 首先，安装依赖库和软件包：
   ```
   yum -y install flex byacc libpcap ncurses ncurses-devel libpcap-devel
   ```
2. 获取iftop源码包：
   ```
   wget http://www.ex-parrot.com/pdw/iftop/download/iftop-0.17.tar.gz
   ```
3. 解压并进入目录：
   ```
   tar zxvf iftop-0.17.tar.gz
   cd iftop-0.17
   ```
4. 配置安装目录（例如，安装在/usr/local/iftop）：
   ```
   ./configure --prefix=/usr/local/iftop
   ```
5. 编译和安装：
   ```
   make && make install
   ```
安装完成后，可以直接运行iftop命令来查看网络流量情况。如果要查看指定网卡的流量，可以使用以下命令：
```
iftop -i eth1
```
其中，`-i` 表示指定网卡接口。
此外，iftop还支持一些其他参数，如`-P`（显示历史流量数据）、`-s`（显示统计信息）等。具体使用方法可以参考iftop的官方文档或相关教程。