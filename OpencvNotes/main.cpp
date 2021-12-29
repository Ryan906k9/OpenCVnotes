#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "imageBasic.hpp"
#include "imageConv.hpp"
#include "noiseGeneration.hpp"
#include "linearFiltering.hpp"
 
using namespace std;
using namespace cv;

// Opencv 提供了 Mat 类用于存储矩阵数据，可以理解为一个指向矩阵数据的指针
Mat src1, src2, dst, src_gray;

char* window_name = (char*)"Demo";

/**
 * @主函数
 */
int main( int argc, char** argv )
{
//    2.1 存储图像的容器
//    ImageBasic1();
//    2.2 图像读取，显示
//    ImageBasic2();
//    2.3 加载视频，调用摄像头
//    ImageBasic3();
//    2.4 保存数据
//    2.4.1 保存图片
//    SaveImage();
//    2.4.2 保存视频
//    SaveVideo();
//    2.4.3 对 XML 和 YMAL 文件操作
//    TestXMLandXMAL();
    
    
//    3 图像的基本操作
//    3.1 图像色彩空间
    
//    5 图像滤波
//    5.1 图像卷积
//    TestImageConv();
//    5.2 噪声的生成
//    5.2.1 椒盐噪声
//    generateSaltAndPepperNoise();
//    5.2.2 高斯噪声
//    generateGaussNoise();
//    5.3 线性滤波
//    5.3.1 均值滤波
//    TestMeanFilter();
//    5.3.2 方框滤波
//    TestBoxFilter();
//    5.3.3 高斯滤波
    TestGaussFilter();
//    5.3.4 可分离滤波
    TestSepFilter();
    
//    /// 读取一副图片
//    src1 = imread("./data/fruits.jpg");
//    src2 = src1;
//
//    /// 将图片转成灰度图片
//    cvtColor(src2, src_gray, COLOR_RGB2GRAY);
//    namedWindow(window_name, WINDOW_AUTOSIZE);
//    imshow(window_name, src_gray);
//
//    while(true) {
//        int c;
//        c = waitKey(20);
//        if (27 == (char) c) {
//            break;
//        }
//    }
}
