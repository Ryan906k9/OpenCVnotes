//
//  imageConv.cpp
//  OpencvNotes
//  第五章 图像滤波
//  5.1 图像卷积
//  Created by Ray on 2021/12/28.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include "imageConv.hpp"

//  图像滤波的目的：去除图像内的噪声
//  需要卷积模板/卷积核，该卷积模板在原始图片上移动，对覆盖区域进行点乘（元素乘）
//  覆盖区域中心点的值，即为覆盖区域所有点乘结果求和
//
//  在数学意义上的卷积，包含以下5个步骤：
//  1. 卷积核旋转 180 度（深度学习中 CNN 无需这个步骤）
//  2. 卷积核中心对准目标像素点
//  3. 计算覆盖区域的点乘，并求和
//  4. 将得到的值存放于对应像素点位置
//  5. 从左到右，从上到下平移卷积核，知道遍历原始图像
//
//  为了防止卷积后发生数据溢出，通常会通过缩放让卷积核所有的值和为 1
//
//  使用 filter2D() 进行卷积，对多通道图像，如果不同通道需要用不同的卷积核，需要先 split() 将多个通道分离开
//  卷积核通常是奇数尺寸，3*3，5*5
//  void cv::filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor = Point(-1,-1), double delta =  0, int borderType = BORDER_DEFAULT)

void TestImageConv()
{
    // 初始化数据
    uchar points[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    // 生成矩阵
    // 1   2  3  4
    // 5   6  7  8
    // 9  10 11 12
    // 13 14 15 16
    cv::Mat mat(4, 4, CV_8UC1, points);
    // 定义卷积核
    // 1 2 1
    // 1 0 1
    // 1 2 1
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1,2,1,1,0,1,1,2,1);
//    cv::Mat kernel = (cv::Mat_<float>(3, 3) << -1,0,1,-1,0,1,-1,0,1);
    // float 对应的类型是 CV_32FC1
    // 卷积核归一化
    cv::Mat kernel_norm = kernel / 10;
    // 初始化结果变量
    cv::Mat result, result_norm;
    // 进行卷积
    cv::filter2D(mat, result, CV_32F, kernel, cv::Point(-1,-1), 3.0, cv::BORDER_CONSTANT);
    // 数据类型（深度）为 CV_32F，当赋值 -1 时输出图像数据类型自动选择
    // Point(-1,-1) 为默认选项，表示基准点是 kernel 的中心
    // 偏置 delta = 3.0
    // 像素外推设置，BORDER_CONSTANT 表示特定值填充
    //      默认的 BORDER_DEFAULT 表示不包含边界值的倒序填充，比如 1234 填充后为：432|1234|321
    cv::filter2D(mat, result_norm, CV_32F, kernel_norm, cv::Point(-1,-1), 3.0, cv::BORDER_CONSTANT);
    // 显示卷积结果
    std::cout << "result: " << std::endl << result << std::endl;
    std::cout << "result_norm: " << std::endl << result_norm << std::endl;
    // result 中 (1,1) 的值为 12
    // 1*0+2*0+1*0 + 1*0+0*1+1*2 + 1*0+2*5+1*6 + 3.0 = 21
    
    // 图像卷积
    cv::Mat lena = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please check the image!" << std::endl;
        return;
    }
    cv::Mat lena_result;
    cv::filter2D(lena, lena_result, -1, kernel_norm);
    cv::imshow("lena_origin", lena);
    cv::imshow("lena_conv", lena_result);
    cv::waitKey(0);
    return;
}
