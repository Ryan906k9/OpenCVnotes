//
//  ImageBasic.cpp
//  OpencvNotes
//  第二章 数据载入，显示，保存
//  Created by Ray on 2021/12/21.
//
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/gapi/own/types.hpp>
#include "ImageBasic.hpp"
#include <iostream>

//using namespace std;

// 2.1 存储图像的容器
void imageBasic1()
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
    // std::cout<< src4 << std::endl; // 打印数据查看
    
    cv::Mat src5(4, 4, CV_8UC1); // 单通道矩阵
    cv::Mat src6(4, 4, CV_8U); // 与上面等价，默认是单通道
    // 注意，这里的类型只能用 OpenCV 定义的数据类型，不能用 double, float 等
    // 而在之前的 Mat_<double>(3,4) 中，不能使用 OpenCV 定义的数据类型！
    
    // 2.1.2 Mat 类的构造与赋值
    // 1. Mat 类构造
    // （1） 默认构造函数
    // cv::Mat::Mat()
    // 无需任何参数，后续变量赋值的时候自动判断，灵活，用于读取数据，存储运算结果等
    cv::Mat a1;
    
    // （2） 输入尺寸和类型
    // cv::Mat::Mat( int rows, int cols, int type)
    cv::Mat a2(3, 5, CV_8UC3);
    // 虽然图片是 3 通道的，但是矩阵可以有更多通道，利用 C(n) 中的 n 可以最大取到 512
    
    // cv::Mat::Mat(Size size(), int type)
    cv::Mat a3(cv::Size(2, 3), CV_32FC(64));
    // 注意，利用 Size 后 2 是 列数量（宽度），3 是行的数量（高度），这与直接输入矩阵维度是相反的
    // 这里的 C(64) 即表示 64 通道
    
    // （3） 利用已有矩阵构造
    // cv::Mat::Mat( const Mat & m)
    cv::Mat a4(a3); // 仅仅是复制了指针，指向的矩阵地址是同一个
    cv::Mat a5 = a3.clone(); // 完全复制
    
    // cv::Mat::Mat(const Mat & m, const Range & rowRange, const Range & colRange = Range::all())
    cv::Mat a6(a2, cv::Range(1,2), cv::Range(4,5)); // 也是指向同一个地址！！！
    // 通过 a2 来创建，a2 是 3*5 维度，截取1～2行，4～5列，最终 a6 维度 2*2
    cv::Mat a7(a2, cv::Range(1,2)); // 列范围取默认
    
    // 2. Mat 类赋值
    // （1）构造时候赋值
    // cv::Mat::Mat(int rows, int cols, int type, const Scalar & s)
    cv::Mat a8(3, 4, CV_8UC3, cv::Scalar(0, 100, 255));
    // 构建 3 通道矩阵，每个像素点值都是 (0, 100, 255)
    cv::Mat a9(1, 2, CV_8UC1, cv::Scalar(100));
    // 构建 单通道矩阵，每个像素点值都是 100
    // 注意，如果 Scalar 中的数据个数大于通道数，后面的会被舍去，不足的会补 0
    
    // （2）枚举赋值
    cv::Mat a10 = (cv::Mat_<int>(2, 2) << 1, 2, 3, 4);
    // 第一行 2 个元素为 1，2，第二行 2 个元素为 3，4
    cv::Mat a11 = (cv::Mat_<double>(2, 3) << 1.1, 2.1, 3.0, 4.1, 5.2, 6.3);
    // 注意，这里外面的括号是一定要加的。该方法在实际中较少使用
    
    // （3）循环赋值
    cv::Mat a12 = cv::Mat_<int>(3, 4);
    for ( int i = 0; i < a12.rows; i++){
        for ( int j = 0; j < a12.cols; j++){
            a12.at<int>(i, j) = i; // 每一个元素都赋值为对应的行号
            // 注意，这里 at 后面的 <int> 不能少，表示初始化矩阵时元素的类型，后面跟着赋的值也必须是这个类型
        }
    }
    
    // （4）类方法赋值
    cv::Mat a13 = cv::Mat::eye(3, 4, CV_8U); // 构造单位矩阵
    cv::Mat a14 = (cv::Mat_<int>(1, 3) << 1, 2, 3);
    cv::Mat a15 = cv::Mat::diag(a14); // 构造对角矩阵，需要传入一维变量作为对角线值
    cv::Mat a16 = cv::Mat::ones(2, 3, CV_8U); // 构造全 1 矩阵
    cv::Mat a17 = cv::Mat::zeros(2, 2, CV_8U); // 构造全 0 矩阵
    
    // （5）数组赋值
    float a18[8] = {1.1, 2.2, 3, 4, 5.1, 6.2, 7, 8};
    cv::Mat a19 = cv::Mat(2, 2, CV_32FC2, a18);
    cv::Mat a20 = cv::Mat(2, 3, CV_32FC1, a18);
    // std::cout << a19 << std::endl;
    // [1.1, 2.2, 3, 4;
    // 5.0999999, 6.1999998, 7, 8]
    // 先是第 1 个像素的 2 个通道 1.1 和 2.2，然后是第 2 个像素 3 和 4
    // 然后是 第 2 行 赋值
    // 注意：
    // 浮点数在内存中的存储机制和整型数不同，其有舍入误差，在计算机中用近似表示任意某个实数。具体的说，这个实数由一个整数或定点数（即尾数）乘以某个基数（计算机中通常是2）的整数次幂得到，这种表示方法类似于基数为10的科学记数法。所以浮点数在运算过程中通常伴随着因为无法精确表示而进行的近似或舍入。但是这种设计的好处是可以在固定的长度上存储更大范围的数。
    //
    // std::cout << a20 << std::endl;
    // [1.1, 2.2, 3;
    // 4, 5.0999999, 6.1999998]
    
    // 2.1.3 Mat 类的运算
    // Mat 类支持矩阵的加减乘除运算
    // （1）与常数运算
    cv::Mat a21 = cv::Mat::ones(2, 3, CV_32FC(1));
    cv::Mat a22, a23, a24, a25;
    a22 = a21 + 2.0;
    // std::cout << a22 << std::endl;
    // [3, 3, 3;
    // 3, 3, 3]
    a23 = a21 - 3;
    // std::cout << a23 << std::endl;
    // [-2, -2, -2;
    // -2, -2, -2]
    a24 = a21 * 4;
    // std::cout << a24 << std::endl;
    // [4, 4, 4;
    // 4, 4, 4]
    a25 = a21 / 2.0;
    // std::cout << a25 << std::endl;
    // [0.5, 0.5, 0.5;
    // 0.5, 0.5, 0.5]
    // 注意：
    // Mat 类型与常数进行运算，结果保留 Mat 的数据类型
    
    // (2) 矩阵与矩阵运算
    
    
    
}
