#pdf转txt(用ocr识别图片) cpu处理 (debuing)

#pdf分割转png
import os
#os.environ["KMP_DUPLICATE_LIB_OK"]="TRUE" #easyocr 可能会出现无法导入的问题 遂可以加入这句话

import fitz  # 来自 PyMuPDF
import easyocr
from PIL import Image

def pdf_to_images_and_save(pdf_path, output_folder):
    # 创建新文件夹
    os.makedirs(output_folder, exist_ok=True)

    # 打开 PDF 文件
    pdf_document = fitz.open(pdf_path)

    # 遍历每一页
    for page_number in range(pdf_document.page_count):
        # 获取页面对象
        page = pdf_document[page_number]

        # 获取页面的图像
        image_list = page.get_pixmap()

        # 将 Pixmap 转换为 PIL Image
        image = Image.frombytes("RGB", [image_list.width, image_list.height], image_list.samples)

        # 保存图像为 PNG 文件
        image_path = os.path.join(output_folder, f"{page_number + 1}.png")
        image.save(image_path, "PNG")

# 使用示例
pdf_file_path = 'C:/Users/i12cu84/filename.pdf'
output_folder_path = 'C:/Users/i12cu84/dir'

pdf_to_images_and_save(pdf_file_path, output_folder_path)

#识别png转txt
import os

def process_png_directory(png_folder, txt_filename):
    # 初始化 EasyOCR
    reader = easyocr.Reader(['ch_sim'])  # 默认语言设置为中文，根据需要可以更改

    # 获取 PNG 文件列表并按数字排序
    png_files = sorted([f for f in os.listdir(png_folder) if f.lower().endswith('.png')], key=lambda x: int(os.path.splitext(x)[0]))

    # 遍历 PNG 文件
    with open(txt_filename, 'a', encoding='utf-8') as txt_file:
        for png_file in png_files:
            # 构建 PNG 文件的绝对路径
            png_path = os.path.join(png_folder, png_file)

            # 使用 EasyOCR 识别图片内容
            text = reader.readtext(png_path)

            # 将识别的内容写入 txt 文件
            txt_file.write(f"\n\n{png_file}:\n")
            txt_file.write('\n'.join([result[1] for result in text]))

# 使用示例

png_folder_path =  'C:/Users/i12cu84/666/'
txt_file_name = 'C:/Users/i12cu84/file.txt'

process_png_directory(png_folder_path, txt_file_name)

#删除存储的png 并告知完成