import os

def compare_txt_files(file_a_path, file_b_path, output_c_path, output_d_path):
    """
    比较两个txt文件，将A中有B中没有的行输出到C文件，将B中有A中没有的行输出到D文件
    
    参数:
    file_a_path: 文件A的路径
    file_b_path: 文件B的路径  
    output_c_path: 输出文件C的路径（A有B无）
    output_d_path: 输出文件D的路径（B有A无）
    """
    
    try:
        # 读取文件A的内容
        with open(file_a_path, 'r', encoding='utf-8') as file_a:
            lines_a = set(line.strip() for line in file_a if line.strip())
        
        # 读取文件B的内容
        with open(file_b_path, 'r', encoding='utf-8') as file_b:
            lines_b = set(line.strip() for line in file_b if line.strip())
        
        # 找出A中有但B中没有的行
        a_minus_b = lines_a - lines_b
        
        # 找出B中有但A中没有的行
        b_minus_a = lines_b - lines_a
        
        # 将结果写入文件C（A有B无）
        with open(output_c_path, 'w', encoding='utf-8') as file_c:
            for line in sorted(a_minus_b):
                file_c.write(line + '\n')
        
        # 将结果写入文件D（B有A无）
        with open(output_d_path, 'w', encoding='utf-8') as file_d:
            for line in sorted(b_minus_a):
                file_d.write(line + '\n')
        
        # 打印统计信息
        print(f"比较完成！")
        print(f"文件A总行数: {len(lines_a)}")
        print(f"文件B总行数: {len(lines_b)}")
        print(f"输出到文件C的行数(A有B无): {len(a_minus_b)}")
        print(f"输出到文件D的行数(B有A无): {len(b_minus_a)}")
        print(f"共同存在的行数: {len(lines_a & lines_b)}")
        
    except FileNotFoundError as e:
        print(f"文件未找到: {e}")
    except Exception as e:
        print(f"发生错误: {e}")

def get_script_directory():
    """获取当前Python脚本所在的目录路径"""
    return os.path.dirname(os.path.abspath(__file__))

def compare_txt_files_in_same_directory():
    """
    自动将ABCD四个文件放在Python代码的同路径下
    """
    # 获取当前脚本所在目录
    script_dir = get_script_directory()
    
    # 构建文件路径（放在同一目录下）
    file_a = os.path.join(script_dir, "A.txt")
    file_b = os.path.join(script_dir, "B.txt")
    output_c = os.path.join(script_dir, "C.txt")
    output_d = os.path.join(script_dir, "D.txt")
    
    print(f"脚本所在目录: {script_dir}")
    print(f"文件A路径: {file_a}")
    print(f"文件B路径: {file_b}")
    print(f"输出文件C路径: {output_c}")
    print(f"输出文件D路径: {output_d}")
    print("-" * 50)
    
    # 检查输入文件是否存在
    if not os.path.exists(file_a):
        print(f"错误: 文件A不存在 - {file_a}")
        return
    if not os.path.exists(file_b):
        print(f"错误: 文件B不存在 - {file_b}")
        return
    
    # 调用比较函数
    compare_txt_files(file_a, file_b, output_c, output_d)

# 使用示例
if __name__ == "__main__":
    compare_txt_files_in_same_directory()