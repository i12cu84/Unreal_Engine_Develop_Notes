#统计输入字符串在目标txt中出现的次数
import os

# 输入字符串
input_string = input("请输入要统计的字符串：")

# 获取当前目录下所有的.txt文件
txt_files = [f for f in os.listdir('.') if f.endswith('.txt')]

# 初始化计数器
count_dict = {}

# 遍历所有.txt文件
for file_name in txt_files:
    # 打开并读取文件内容
    with open(file_name, 'r', encoding='utf-8') as file:
        content = file.read()
        # 统计字符串出现的次数并累加
        count = content.count(input_string)
        count_dict[file_name] = count

# 输出结果
for file_name, count in count_dict.items():
    print(f"字符串'{input_string}'在文件'{file_name}'中出现了{count}次。")
