#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "ImageBasic.hpp"
 
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
    imageBasic();
    /// 读取一副图片
//    src = imread(argv[1], 1 );
    src1 = imread("./data/fruits.jpg");
    src2 = src1;
    // 这里 src1 和 src2 都指向同一个矩阵，通过一个矩阵头修改矩阵，另一个的数据也会发生变化
    // 只有同时删除两个矩阵头，矩阵数据才会被释放
    // 矩阵头中存放了矩阵数据的引用次数，当次数为 0 的时候释放数据，避免错误释放，并节约内存空间
    // 存储类型可以包含 double, float, uchar, unsigned char, 自定义模版
    
    // 我们可以指定数据类型
    cv::Mat src3 = Mat_<double>(3,4); // 创建 3*4 矩阵，矩阵内数据类型为 double
    
    // 创建不同的位图
    cv::Mat src4(64, 64, CV_8UC3);
    // 这里创建了 64*64 的图片，CV_8U 表示8位无符号，范围 0～255 （有符号用 8S）
    // C3 表示 3 通道，即彩色图片
    cv::Mat src5(4, 4, CV_8UC1); // 单通道矩阵
    cv::Mat src6(4, 4, CV_8U); // 与上面等价，默认是单通道
    // 注意，这里的类型只能用 OpenCV 定义的数据类型，不能用 double, float 等
    // 而在之前的 Mat_<double>(3,4) 中，不能使用 OpenCV 定义的数据类型！
    

    /// 将图片转成灰度图片
    cvtColor(src2, src_gray, COLOR_RGB2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, src_gray);

    while(true) {
        int c;
        c = waitKey(20);
        if (27 == (char) c) {
            break;
        }
    }
}
