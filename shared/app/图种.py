import subprocess

# 定义变量存储路径
source_png_path = 'C:\\Users\\i12cu84\\Desktop\\1.png'
source_rar_path = 'C:\\Users\\i12cu84\\Desktop\\2.rar'
destination_png_path = 'C:\\Users\\i12cu84\\Desktop\\3.png'

# 调用CMD指令
result = subprocess.run(['cmd.exe', '/c', 'copy /b ' + source_png_path + '+' + source_rar_path + ' ' + destination_png_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

# 获取输出
stdout = result.stdout
stderr = result.stderr

print("标准输出：")
print(stdout)

print("标准错误：")
print(stderr)

# 检查指令是否成功执行
if result.returncode == 0:
    print("指令成功执行")
else:
    print("指令执行错误")
