Tetris
======

图形学大作业之奇葩俄罗斯方块

display.cpp是用来呈现图形的。画图的代码基本上都在void drawTetris()里面编写和实现，也可以编写其他函数辅助drawTetris的实现。有关计算方块的形状、位置、排列等函数都应在其他文件中实现，此文件只负责在指定位置呈现出图形。

Headers\是放置.h头文件的。主敲display.cpp的人有义务维护Headers\文件夹，在里面添加头文件，列出自己需要的结构定义和函数声明，再交由其他开发者实现。

Sources\是放置.cpp源文件的。开发者从Headers\里面挑选自己想要实现的头文件，在此文件夹中用同名cpp实现。

CodeBlocks如果提示找不到.dll，直接把那个.dll跟.exe放在一起即可(.dll放在system32不见效的情况下使用这招)。

茫琎WE旋转（目前只做了E）
