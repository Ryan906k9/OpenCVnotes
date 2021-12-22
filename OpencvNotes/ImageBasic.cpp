//
//  ImageBasic.cpp
//  OpencvNotes
//
//  Created by Ray on 2021/12/21.
//
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/gapi/own/types.hpp>
#include "ImageBasic.hpp"
#include <iostream>

void imageBasic()
{
    cv::Mat src1;
    src1 = cv::imread("./data/fruits.jpg");
    cv::Mat src2 = src1;
    // 这里 src1 和 src2 都指向同一个矩阵，通过一个矩阵头修改矩阵，另一个的数据也会发生变化
    // 只有同时删除两个矩阵头，矩阵数据才会被释放
    // 矩阵头中存放了矩阵数据的引用次数，当次数为 0 的时候释放数据，避免错误释放，并节约内存空间
    // 存储类型可以包含 double, float, uchar, unsigned char, 自定义模版
    
    // 我们可以指定数据类型
    cv::Mat src3 = cv::Mat_<double>(3,4); // 创建 3*4 矩阵，矩阵内数据类型为 double
    
    // 创建不同的位图
    cv::Mat src4(64, 64, CV_8UC3);
    // 这里创建了 64*64 的图片，CV_8U 表示8位无符号，范围 0～255 （有符号用 8S）
    // C3 表示 3 通道，即彩色图片
    std::cout<< src4 << std::endl;
    
    cv::Mat src5(4, 4, CV_8UC1); // 单通道矩阵
    cv::Mat src6(4, 4, CV_8U); // 与上面等价，默认是单通道
    // 注意，这里的类型只能用 OpenCV 定义的数据类型，不能用 double, float 等
    // 而在之前的 Mat_<double>(3,4) 中，不能使用 OpenCV 定义的数据类型！
    
    // 2.1.2 Mat 类的构造方式
    // 1. 默认构造函数
    // cv::Mat::Mat()
    // 无需任何参数，后续变量赋值的时候自动判断，灵活，用于读取数据，存储运算结果等
    cv::Mat a1;
    
    // 2. 输入尺寸和类型
    // cv::Mat::Mat( int rows, int cols, int type)
    cv::Mat a2(3, 5, CV_8UC3);
    // 虽然图片是 3 通道的，但是矩阵可以有更多通道，利用 C(n) 中的 n 可以最大取到 512
    
    // cv::Mat::Mat(Size size(), int type)
    cv::Mat a3(cv::Size(2, 3), CV_32FC(64));
    // 注意，利用 Size 后 2 是 列数量（宽度），3 是行的数量（高度），这与直接输入矩阵维度是相反的
    // 这里的 C(64) 即表示 64 通道
    
    // 3. 利用已有矩阵构造
    // cv::Mat::Mat( const Mat & m)
    cv::Mat a4(a3); // 仅仅是复制了指针，指向的矩阵地址是同一个
    cv::Mat a5 = a3.clone(); // 完全复制
    
    // cv::Mat::Mat(const Mat & m, const Range & rowRange, const Range & colRange = Range::all())
    
}
