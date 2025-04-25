import os
import sys
import ctypes
from ctypes import wintypes

# Windows 系统簇大小缓存
cluster_cache = {}

def get_cluster_size_windows(path):
    """获取Windows系统中文件所在磁盘的簇大小"""
    drive = os.path.splitdrive(path)[0]
    if not drive:
        drive = os.path.abspath(path)[:2]
    if drive in cluster_cache:
        return cluster_cache[drive]
    
    # 定义Windows API函数
    GetDiskFreeSpaceW = ctypes.windll.kernel32.GetDiskFreeSpaceW
    GetDiskFreeSpaceW.argtypes = [
        wintypes.LPCWSTR,
        ctypes.POINTER(wintypes.DWORD),
        ctypes.POINTER(wintypes.DWORD),
        ctypes.POINTER(wintypes.DWORD),
        ctypes.POINTER(wintypes.DWORD),
    ]
    GetDiskFreeSpaceW.restype = wintypes.BOOL

    # 准备参数
    sectors_per_cluster = wintypes.DWORD()
    bytes_per_sector = wintypes.DWORD()
    free_clusters = wintypes.DWORD()
    total_clusters = wintypes.DWORD()

    # 调用API
    if not GetDiskFreeSpaceW(
        drive,
        ctypes.byref(sectors_per_cluster),
        ctypes.byref(bytes_per_sector),
        ctypes.byref(free_clusters),
        ctypes.byref(total_clusters),
    ):
        raise ctypes.WinError()
    
    cluster_size = sectors_per_cluster.value * bytes_per_sector.value
    cluster_cache[drive] = cluster_size
    return cluster_size

def get_allocated_size(file_path):
    """获取文件实际磁盘占用空间"""
    if os.name == 'nt':
        # Windows系统计算方式
        file_size = os.path.getsize(file_path)
        cluster_size = get_cluster_size_windows(file_path)
        return ((file_size + cluster_size - 1) // cluster_size) * cluster_size
    else:
        # Unix系统计算方式 (Linux/MacOS)
        return os.stat(file_path).st_blocks * 512

def collect_file_info(root_dir):
    """收集目录下所有文件信息"""
    file_info_list = []
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            file_path = os.path.join(dirpath, filename)
            absolute_path = os.path.abspath(file_path)
            try:
                # 获取文件信息
                size_bytes = get_allocated_size(file_path)
                file_info = {
                    '文件名': filename,
                    '绝对路径': absolute_path,
                    '占用空间(GB)': size_bytes / (1024 ** 3),
                    '占用空间(KB)': size_bytes / 1024,
                    '字节数': os.path.getsize(file_path)
                }
                file_info_list.append(file_info)
            except Exception as e:
                print(f"处理文件失败 {file_path}: {str(e)}")
    return file_info_list

def parse_existing_md(content):
    """解析现有Markdown文件中的表格数据"""
    lines = content.split('\n')
    table_data = {}
    header = []
    pre_content = []
    post_content = []
    in_table = False

    for i, line in enumerate(lines):
        if line.startswith('|') and '绝对路径' in line and '文件名' in line:
            # 找到表头
            header = [col.strip() for col in line.split('|')[1:-1]]
            in_table = True
            pre_content = lines[:i]
            continue
        
        if in_table and line.startswith('|') and '---' in line:
            # 跳过分隔行
            continue
        
        if in_table and line.startswith('|'):
            # 处理数据行
            cols = [col.strip() for col in line.split('|')[1:-1]]
            if len(cols) != len(header):
                continue
            row = dict(zip(header, cols))
            try:
                row['占用空间(GB)'] = float(row['占用空间(GB)'])
                row['占用空间(KB)'] = float(row['占用空间(KB)'])
                row['字节数'] = int(row['字节数'])
                table_data[row['绝对路径']] = row
            except ValueError:
                continue
        
        if in_table and not line.startswith('|'):
            # 表格结束
            post_content = lines[i:]
            break

    return table_data, '\n'.join(pre_content), '\n'.join(post_content)

def generate_md_table(data):
    """生成Markdown表格"""
    headers = ['文件名', '绝对路径', '占用空间(GB)', '占用空间(KB)', '字节数']
    table = ['| ' + ' | '.join(headers) + ' |']
    table.append('|-' + '-|-'.join(['-'*len(h) for h in headers]) + '-|')
    
    for item in sorted(data, key=lambda x: x['占用空间(KB)'], reverse=True):
        row = [
            item['文件名'],
            item['绝对路径'],
            f"{item['占用空间(GB)']:.2f}",
            f"{item['占用空间(KB)']:.2f}",
            str(item['字节数'])
        ]
        table.append('| ' + ' | '.join(row) + ' |')
    
    return '\n'.join(table)

def main(scan_path, md_path):
    # 收集新文件信息
    new_files = collect_file_info(scan_path)
    
    # 读取并合并现有数据
    existing_data = {}
    pre_content = ''
    post_content = ''
    
    if os.path.exists(md_path):
        with open(md_path, 'r', encoding='utf-8') as f:
            content = f.read()
        existing_data, pre_content, post_content = parse_existing_md(content)
    
    # 合并数据（新数据覆盖旧数据）
    for item in new_files:
        existing_data[item['绝对路径']] = item
    
    # 生成新表格
    final_table = generate_md_table(list(existing_data.values()))
    
    # 组合最终内容
    new_content = f"{pre_content}\n{final_table}\n{post_content}".strip()
    
    # 写入文件
    with open(md_path, 'w', encoding='utf-8') as f:
        f.write(new_content)

if __name__ == '__main__':
    """2
    if len(sys.argv) != 3:
        print("使用方法: python script.py <扫描路径> <Markdown文件路径>")
        sys.exit(1)
    """

    scan_path = r"F:"
    md_path = r"E:\Download\data.md"
    
    main(scan_path, md_path)
    print("文件信息已更新至Markdown表格")