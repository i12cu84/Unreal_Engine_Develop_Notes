下载ocr库

```
python -m venv myenv
myenv\Scripts\activate  # 在 Windows 上激活虚拟环境
source myenv/bin/activate  # 在 Linux 或 macOS 上激活虚拟环境
pip install easyocr
```

mistake:
```
>>> import easyocr
OMP: Error #15: Initializing libiomp5md.dll, but found libiomp5md.dll already initialized.
OMP: Hint This means that multiple copies of the OpenMP runtime have been linked into the program. That is dangerous, since it can degrade performance or cause incorrect results. The best thing to do is to ensure that only a single OpenMP runtime is linked into the process, e.g. by avoiding static linking of the OpenMP runtime in any library. As an unsafe, unsupported, undocumented workaround you can set the environment variable KMP_DUPLICATE_LIB_OK=TRUE to allow the program to continue to execute, but that may cause crashes or silently produce incorrect results. For more information, please see http://www.intel.com/software/products/support/.
```

method:
```
import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'
import easyocr
```

