# QCustomPlot 绘制多条动态曲线性能测试

## QCustomPlot
QCustomPlot是一个开源的基于Qt的第三方绘图库，能够绘制漂亮的2D图形。
QCustomPlot的官方网址：https://www.qcustomplot.com/
从官网下载QCustomPlot的源文件，包括qcustomplot.h和qcustomplot.cpp。

## XCustomPlot
XCustomPlot是一个基于QCustomPlot的二次开发的图表类XxwCustomPlot，在该图表中，鼠标跟随动态显示曲线上的点的值，可通过showTracer(bool)来显示或隐藏。

## LXCustomPlot
LXCustomPlot是基于QCustomPlot和XCustomPlot，创建10条动态曲线，测试绘制性能，可以在LXCustomPlot.cpp构造函数打开和关闭opengl
