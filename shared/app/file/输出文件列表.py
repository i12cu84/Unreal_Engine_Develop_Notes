#依照文件大小降序输出文件列表
import os

def get_file_size(file_path):
    return os.path.getsize(file_path)

def sort_files_by_size(folder_path):
    # 获取文件夹中的所有文件
    file_paths = [os.path.join(folder_path, f) for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
    # 按文件大小降序排序
    file_paths.sort(key=get_file_size, reverse=True)
    return file_paths

def print_files_sorted_by_size(folder_path, output_file):
    # 获取排序后的文件列表
    file_paths = sort_files_by_size(folder_path)
    # 打开文件以写入，指定编码格式为UTF-8
    with open(output_file, 'w', encoding='utf-8') as f:
        # 输出文件名和大小
        for file_path in file_paths:
            file_size = get_file_size(file_path)
            #f.write(f"{os.path.basename(file_path)}\n({file_size / 1024:.2f} KB)\n")
            #f.write(f"{os.path.basename(file_path)} ({file_size / 1024:.2f} KB)\n")
            f.write(f"{os.path.basename(file_path).rpartition('.')[0]}\n")# ({file_size / 1024:.2f} KB)\n")
            #f.write(f"{os.path.basename(file_path).rpartition('.')[0]}\n({file_size / 1024:.2f} KB)\n")

folder_path = r"D:\music"  # 替换为你的文件夹路径
output_file = r"C:\Users\chru\Desktop\file_sizes.txt"  # 输出文件的路径和名称
print_files_sorted_by_size(folder_path, output_file)
