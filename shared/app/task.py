import os
import easyocr
from PyPDF2 import PdfReader, PdfWriter
from io import BytesIO
import numpy as np

# 初始化EasyOCR
reader = easyocr.Reader(['ch_sim'])  # 默认语言设置为英文，根据需要可以更改

def process_pdf(pdf_path, output_folder):
    # 读取PDF文件
    pdf = PdfReader(pdf_path)
    all_text = ""
    # 遍历PDF的每一页
    for page in pdf.pages:
        # 使用get_content()方法获取页面内容
        page_content = page.extract_text()
        # 使用easyocr识别页面内容
        text = reader.readtext(page_content)
        # 合并所有文本
        all_text += '\n'.join(text)

    # 将提取的文本保存到输出文件夹
    with open(os.path.join(output_folder, 'extracted_text.txt'), 'w', encoding='utf-8') as f:
        f.write(all_text)

# 使用示例
process_pdf('123.pdf', 'output_folder')
