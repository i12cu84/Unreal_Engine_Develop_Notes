#网易云音乐缓存转mp3
import os
import re
import requests
import json

def generate_files(path):
    # 初始化一个字典，用于将歌曲ID映射到文件名
    id2file = {}
    # 获取指定路径下的所有文件列表
    files = os.listdir(path)
    # 遍历路径中的每个文件
    for file in files:
        # 检查文件是否以'.uc'结尾
        if file.endswith('.uc'):
            # 使用正则表达式匹配文件名中的数字部分
            match_inst = re.match('\d*', file)
            # 如果匹配成功，获取歌曲ID
            if match_inst:
                song_id = match_inst.group()
                # 构建歌曲详情的URL
                url = f'http://music.163.com/api/song/detail/?id={song_id}&ids=%5B{song_id}%5D'
                # 发送HTTP GET请求获取歌曲详情
                response = requests.get(url)
                # 解析响应内容为JSON格式
                jsons = response.json()
                # 获取歌曲名称
                song_name = jsons['songs'][0]['name']
                # 获取歌手名称
                singer_name = jsons['songs'][0]['artists'][0]['name']
                # 构建完整的文件路径
                full_file_path = os.path.join(path, file)
                # 以二进制读取模式打开UC文件
                with open(full_file_path, 'rb') as f:
                    # 读取UC文件内容
                    uc_content = f.read()
                    # 将UC文件内容转换为字节数组
                    mp3_content = bytearray(uc_content)
                    # 对字节数组中的每个字节进行异或操作，以转换格式
                    for i in range(len(uc_content)):
                        mp3_content[i] ^= 0xa3
                # 构建转换后的MP3文件名
                mp3_file_name = f'{path}/{singer_name} - {song_name}.mp3'
                # 以二进制写入模式打开新的MP3文件
                with open(mp3_file_name, 'wb') as mp3_file:
                    # 将转换后的内容写入MP3文件
                    mp3_file.write(mp3_content)
                    # 打印成功转换的MP3文件名
                    print(f'success {mp3_file_name}')

# 指定歌曲缓存路径
path = r'C:/Users/i12cu84/Downloads/Cache/'
# 调用函数开始处理歌曲文件
generate_files(path)
