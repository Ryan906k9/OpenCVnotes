//
//  noiseGeneration.cpp
//  OpencvNotes
//  第五章 图像滤波
//  5.2 噪声的生成
//  Created by Ray on 2021/12/28.
//
//#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "noiseGeneration.hpp"

//  5.2.1 椒盐噪声
//  椒盐噪声 salt-and-pepper noise 又被称作脉冲噪声 impulsive noise
//  其会随机改变图像中的像素值
//  目前 opencv 中没有现成的函数可以生成椒盐噪声
//  需要使用随机数生成函数 rand() 来产生，或者 rand_double() 和 rand_int()
//  int cvflann::rand()
//  无需参数，返回 int 类型
//  可以通过求余数的方式来设定上下界，比如 int a = rand()%100 的范围为 0～99
//  double cvflann::rand_double(double high = 1.0, double low = 0)
//  默认返回 0～1 的 double 类型
//  int cvflann::rand_int(int high = RAND_MAX, int low = 0)
//  默认的 RAND_MAX 由系统定义

//  注意：
//  使用的时候需要注明 cvflann:: 的命名空间，因为 stdlib.h 中的同名函数

cv::Mat AddSaltAndPepperNoise(cv::Mat image, int n)
{
    cv::Mat image_process = image.clone(); // 深拷贝，避免改变输入的图像
    for (int k = 0; k < n; ++k) // 添加 n 个噪声点
    {
        // 随机取位置坐标
        int i, j;
        i = std::rand() % image.rows;
        j = std::rand() % image.cols;
        // 随机白噪声和黑噪声
        int white_black = std::rand() % 2;
        if (!white_black) // 白噪声
        {
            if (image.type() == CV_8UC1)
            {
                image_process.at<uchar>(i, j) = 255;
            }
            else
            {
                image_process.at<cv::Vec3b>(i, j)[0] = 255;
                image_process.at<cv::Vec3b>(i, j)[1] = 255;
                image_process.at<cv::Vec3b>(i, j)[2] = 255;
            }
        }
        else // 黑噪声
        {
            if (image.type() == CV_8UC1)
            {
                image_process.at<uchar>(i, j) = 0;
            }
            else
            {
                image_process.at<cv::Vec3b>(i, j)[0] = 0;
                image_process.at<cv::Vec3b>(i, j)[1] = 0;
                image_process.at<cv::Vec3b>(i, j)[2] = 0;
            }
        }
        
    }
    return image_process;
}

void GenerateSaltAndPepperNoise()
{
    cv::Mat lena  = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please chech the image file!" << std::endl;
        return;
    }
    // 转灰度图
    cv::Mat lena_gray;
    cv::cvtColor(lena, lena_gray, cv::COLOR_BGR2GRAY);
    
    // 显示原图
    cv::imshow("lena origin", lena);
    cv::imshow("lena_gray origin", lena_gray);
    
    // 添加椒盐噪声
    cv::Mat lena_salt = AddSaltAndPepperNoise(lena, 10000); // 添加 10000 个噪声点
    cv::Mat lena_gray_salt = AddSaltAndPepperNoise(lena_gray, 10000);
    
    // 显示添加噪声的图片
    cv::imshow("lena origin with noise", lena_salt);
    cv::imshow("lena_gray origin with noise", lena_gray_salt);
    
    cv::waitKey(0);
    return;
}



//  5.2.2 高斯噪声
//  高斯噪声的概率分布符合高斯分布
//  区别于椒盐噪声的随机出现在任意位置，高斯噪声出现在所有位置
//  在 opencv 中没有函数直接产生高斯噪声，可以用 fill() 产生高斯分布/正态分布（该函数也可以产生均匀分布）的随机数，在图像中加入这些随机数即可产生高斯噪声
//  void cv::RNG::fill(InputOutputArray mat, int distType, InputArray a, InputArray b, bool saturateRange = false)
//  mat: 随机数矩阵，仅支持低于 5 通道的矩阵
//  distType: 分布类型，目前仅有均匀分布 RNG::UNIFORM 或者高斯分布 RNG::NORMAL
//  a: 参数，均匀分布中的下限（包含），高斯分布中的均值
//  b: 参数，均匀分布中的上限（不包含），高斯分布中的标准差
//  saturateRange: 预饱和标志，仅适用于均匀分布

cv::Mat AddGaussNoise(cv::Mat mat, float mean, float std)
{
    // 初始化噪声矩阵存放空间
    cv::Mat noise = cv::Mat::zeros(mat.rows, mat.cols, mat.type());
    // 实例化 RNG 类
    cv::RNG rng;
    // 调用生成方法生成噪声矩阵
    rng.fill(noise, cv::RNG::NORMAL, mean, std);
    // 添加噪声
    return mat+noise;
}

void GenerateGaussNoise()
{
    cv::Mat lena  = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please chech the image file!" << std::endl;
        return;
    }
    // 转灰度图
    cv::Mat lena_gray;
    cv::cvtColor(lena, lena_gray, cv::COLOR_BGR2GRAY);
    
    // 显示原图
    cv::imshow("lena origin", lena);
    cv::imshow("lena_gray origin", lena_gray);
    
    // 初始化噪声矩阵存放空间
    cv::Mat lena_noise = cv::Mat::zeros(lena.rows, lena.cols, lena.type());
    cv::Mat lena_gray_noise = cv::Mat::zeros(lena_gray.rows, lena_gray.cols, lena_gray.type());
    
    cv::RNG rng; // 实例化 RNG 类
    // 调用生成方法生成噪声矩阵
    rng.fill(lena_noise, cv::RNG::NORMAL, 10, 20);
    rng.fill(lena_gray_noise, cv::RNG::NORMAL, 15, 30);
    
    // 显示噪声图片
    cv::imshow("3 channels noise", lena_noise);
    cv::imshow("single channel noise", lena_gray_noise);
    
    // 添加噪声
    lena += lena_noise;
    lena_gray += lena_gray_noise;
    
    // 显示添加噪声后的图像
    cv::imshow("lena with noise", lena);
    cv::imshow("lena_gray with noise", lena_gray);
    
    cv::waitKey(0);
    return;
}
