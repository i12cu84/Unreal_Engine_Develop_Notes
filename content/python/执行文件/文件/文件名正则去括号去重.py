import os
import shutil
import re

# 定义文件夹A和B的路径
folder_a = r"D:\newmusic"
folder_b = r"C:\Users\chru\Desktop\del"

# 检查路径是否存在
if not os.path.exists(folder_a) or not os.path.exists(folder_b):
    print(f"文件夹A或文件夹B不存在： {folder_a} 或 {folder_b}")
    exit()

# 遍历文件夹A中的所有文件和文件夹
for filename in os.listdir(folder_a):
    # 检查文件名中是否包含括号
    if '(' in filename and ')' in filename:
        # 使用正则表达式去除括号及其内部内容
        base_filename_without_brackets = re.sub(r'\([^)]*\)', '', filename)
        # 检查去掉括号后的文件名是否存在
        if os.path.exists(os.path.join(folder_a, base_filename_without_brackets)):
            # 移动文件到文件夹B
            shutil.move(os.path.join(folder_a, filename), os.path.join(folder_b, filename))
            print(f"文件 {filename} 已移动到 {folder_b}")
        #else:
            #print(f"文件 {filename} 存在括号，但去掉括号后的文件 {base_filename_without_brackets} 不存在于文件夹A中")
