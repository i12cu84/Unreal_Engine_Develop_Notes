enter(激活事件,取入执行脉冲)
open(开事件,开始持续输出脉冲)
close(关事件,关闭持续输出脉冲)
toggle(对角执行布尔开关,开状态时触发则变成关,反之亦然)

例:
触发open时,不断触发enter,会有exit输出
触发close时,触发enter,不会有任何效果,只有重新触发open时,再触发enter才有效果
