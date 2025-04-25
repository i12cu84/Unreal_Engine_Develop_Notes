"""
RAR文件加密脚本
功能：对指定目录下的所有RAR文件进行加密打包，生成带密码保护的副本
"""

import os
import subprocess
from pathlib import Path
from typing import List, Optional

# ===================== 用户配置区域 =====================
TARGET_DIRECTORY = r"C:\Users\chru\Desktop\UE-VRGK-v2-master"  # 目标目录
ENCRYPTION_PASSWORD = "1234"                                  # 加密密码
OUTPUT_SUFFIX = "_encrypted"                                  # 输出文件后缀
WINRAR_PATHS = [                                             # WinRAR可能路径
    r"C:\Program File\WinRAR\WinRar.exe"  # 容错可能的拼写错误
]
# ======================================================

def find_winrar_executable() -> str:
    """定位WinRAR可执行文件路径"""
    for path in WINRAR_PATHS:
        if os.path.isfile(path):
            return path
    raise FileNotFoundError("未找到WinRAR可执行文件，请检查安装路径")

def find_rar_files(directory: str) -> List[str]:
    """查找目录及其子目录中的所有RAR文件"""
    rar_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower().endswith('.rar'):
                full_path = os.path.join(root, file)
                rar_files.append(full_path)
    return rar_files

def encrypt_rar(winrar_path: str, original_rar: str, password: str) -> Optional[str]:
    """
    使用WinRAR创建加密副本
    返回新文件路径（成功时），None（失败时）
    """
    try:
        original_path = Path(original_rar)
        output_path = original_path.with_name(
            f"{original_path.stem}{OUTPUT_SUFFIX}{original_path.suffix}"
        )

        # 构建WinRAR命令行参数
        command = [
            winrar_path,
            "a",               # 添加文件到压缩包
            "-ep",             # 排除基本路径
            "-hp"+password,    # 加密文件和文件名
            "-ibck",           # 后台运行
            "-r",              # 递归子目录
            "-y",              # 全部确认
            str(output_path),  # 输出文件路径
            str(original_path) # 源文件路径
        ]

        # 执行压缩命令
        result = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True
        )

        if result.returncode == 0:
            print(f"成功加密：{original_path} -> {output_path}")
            return str(output_path)
            
    except subprocess.CalledProcessError as e:
        print(f"加密失败【{original_rar}】: {e.stderr.decode('gbk')}")
    except Exception as e:
        print(f"处理异常【{original_rar}】: {str(e)}")
    
    return None

def main():
    """主处理流程"""
    try:
        # 验证WinRAR路径
        winrar_path = find_winrar_executable()
        print(f"找到WinRAR路径：{winrar_path}")

        # 查找所有RAR文件
        rar_files = find_rar_files(TARGET_DIRECTORY)
        if not rar_files:
            print("未找到需要处理的RAR文件")
            return

        print(f"发现{len(rar_files)}个需要处理的RAR文件")

        # 处理每个文件
        success_count = 0
        for rar_file in rar_files:
            if encrypt_rar(winrar_path, rar_file, ENCRYPTION_PASSWORD):
                success_count += 1

        print(f"处理完成，成功加密{success_count}/{len(rar_files)}个文件")

    except Exception as e:
        print(f"程序异常终止: {str(e)}")

if __name__ == "__main__":
    main()