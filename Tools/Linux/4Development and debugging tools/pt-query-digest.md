 `pt-query-digest` 是一个 Percona Toolkit for MySQL 的组件，用于分析和诊断 MySQL 查询性能问题。它可以解析 MySQL 的查询日志（query log）文件，并生成易于理解的摘要报告，帮助管理员发现慢查询和潜在的性能瓶颈。
要使用 `pt-query-digest`，你需要先安装 Percona Toolkit。以下是一份简要的 `pt-query-digest` 使用指南：
1. 安装 Percona Toolkit：
   ```
   sudo yum install percona-toolkit
   ```
2. 运行 `pt-query-digest`：
   ```
   sudo pt-query-digest /path/to/mysql/query_log.txt
   ```
这里，`/path/to/mysql/query_log.txt` 是你需要分析的 MySQL 查询日志文件的路径。
3. 你可以通过以下命令查看 `pt-query-digest` 生成的报告：
   ```
   less /path/to/pt-query-digest-report.txt
   ```
4. 如果你想要在 HTML 格式下查看报告，可以使用以下命令：
   ```
   sudo pt-query-digest /path/to/mysql/query_log.txt -o /path/to/pt-query-digest-report.html
   ```
5. 如果你想要分析多个 MySQL 服务器的查询日志，可以使用 `-h` 选项指定服务器列表：
   ```
   sudo pt-query-digest -h host1,host2 /path/to/mysql/query_log.txt
   ```
6. 还可以使用 `--config` 选项指定配置文件，以便自定义 `pt-query-digest` 的行为：
   ```
   sudo pt-query-digest --config /path/to/config.txt /path/to/mysql/query_log.txt
   ```
`pt-query-digest` 是一个非常强大的工具，可以帮助你发现 MySQL 查询性能问题。要充分利用它的功能，建议阅读官方文档和教程，了解更多有关如何分析和解决性能问题的信息。