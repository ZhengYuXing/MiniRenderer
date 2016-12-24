# MiniRenderer

一个用C++编写的光栅化渲染器，运行在Linux系统下

    运行方法:
    make
    ./main

    src文件夹 : 源代码
    res文件夹 : 纹理图片和3D模型文件
    image文件夹 : 渲染器生成的图片

## src
    Vector : 定义了三维点和三维向量的加减、点乘、叉乘等基本运算
    Matrix : 定义了4×4矩阵的加减、乘法等基本运算和旋转、平移、缩放等操作
    Color : 定义了rgb颜色对象的基本操作
    Vertex : 定义了顶点对象的插值等基本操作
    Texture : 读取bmp纹理图片的纹理对象
    Mesh : 网格对象，读取三维网格文件并将信息保存至顶点数组和索引数组中
    Renderer : 渲染器对象，定义了画像素点、画直线、画三角形、画网格对象、加载obj网格文件、将渲染的图片保存为bmp图片等操作
    
## images
![image](https://github.com/ZhengYuXing/MiniRenderer/blob/master/image/image1.bmp)
![image](https://github.com/ZhengYuXing/MiniRenderer/blob/master/image/image2.bmp)
![image](https://github.com/ZhengYuXing/MiniRenderer/blob/master/image/image3.bmp)
![image](https://github.com/ZhengYuXing/MiniRenderer/blob/master/image/image4.bmp)
