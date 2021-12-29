//
//  linearFiltering.cpp
//  OpencvNotes
//  第五章 图像滤波
//  5.3 线性滤波
//  Created by Ray on 2021/12/29.
//

#include "linearFiltering.hpp"
#include "opencv2/opencv.hpp"
#include "noiseGeneration.hpp"

//  图像去噪（图像平滑）
//  由于图像噪声集中在高频段，图像去噪可以看作是利用低通滤波器滤波的过程
//  图像特征提取
//  由于图像纹理变化明显的区域频率高，所以高通滤波可以起到提取边缘，增强和锐化图像的效果

//  图像模糊
//  低通滤波后，图像边缘信息弱化，图像变模糊
//  所以低通滤波中，模糊=滤波，比如高斯模糊=高斯低通滤波

//  图像滤波分为：线性滤波，非线形滤波
//  常见线形滤波：均值滤波，方框滤波，高斯滤波
//  常见非线性滤波：中值滤波，双边滤波

//  滤波与卷积过程类似，相比于卷积核，滤波器（滤波模板/领域算子）不需要旋转 180 度
//  通过滤波范围内所有像素之间的线性组合得到中心像素的滤波后的值，即线性滤波

//  5.3.1 均值滤波
//  均值滤波的核心思想是测量多次取平均，即滤波器覆盖的像素看作是中心像素的测量，每个像素权重相等，中心像素为其均值
//  优点：像素值变化趋势一致的情况下，可以去噪
//  缺点：缩小了像素值差距，变得模糊，滤波器范围越大，越是模糊

//  void cv::blur(InputArray src, OutputArray dst, Size ksize, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
//  src: 目标图像
//  dst: 滤波后图像，与输入的尺寸，类型，通道数相同
//  ksize: 滤波器尺寸
//  anchor: 内核基准点，默认（-1，-1），即中心
//  borderType: 像素外推法选择标志

void TestMeanFilter()
{
    // 读取图片
    cv::Mat lena = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please chech the image file!" << std::endl;
        return;
    }
    
    // 调用 "noiseGeneration.hpp" 中的函数添加噪声
    cv::Mat lena_gauss_noise = AddGaussNoise(lena, 10, 20); // 添加高斯噪声，均值 10，标准差 20
    cv::Mat lena_salt_noise = AddSaltAndPepperNoise(lena, 10000); // 添加椒盐噪声，10000 个噪声点
    
    // 显示图像
    cv::imshow("origin lena", lena);
    cv::imshow("lena with gauss noise", lena_gauss_noise);
    cv::imshow("lena with salt noise", lena_salt_noise);
    // 初始化结果矩阵
    cv::Mat result_k3, result_gauss_k3, result_salt_k3, result_k9, result_gauss_k9, result_salt_k9;
    // 均值滤波
    cv::blur(lena, result_k3, cv::Size(3, 3));
    cv::blur(lena_gauss_noise, result_gauss_k3, cv::Size(3, 3));
    cv::blur(lena_salt_noise, result_salt_k3, cv::Size(3, 3));
    cv::blur(lena, result_k9, cv::Size(9, 9));
    cv::blur(lena_gauss_noise, result_gauss_k9, cv::Size(9, 9));
    cv::blur(lena_salt_noise, result_salt_k9, cv::Size(9, 9));
    // 显示结果
    cv::imshow("lena after blur (kernel 3*3)", result_k3);
    cv::imshow("lena_gauss after blur (kernel 3*3)", result_gauss_k3);
    cv::imshow("lena_salt after blur (kernel 3*3)", result_salt_k3);
    cv::imshow("lena after blur (kernel 9*9)", result_k9);
    cv::imshow("lena_gauss after blur (kernel 9*9)", result_gauss_k9);
    cv::imshow("lena_salt after blur (kernel 9*9)", result_salt_k9);
    
    // 结果显示：
    // 滤波器越大，去噪效果越好，但是结果图像也越是模糊
    // 另外，均值滤波对高斯噪声的处理效果好于对椒盐噪声的处理
    
    cv::waitKey(0);
    return;
}


//  5.3.2 方框滤波
//  方框滤波是均值滤波的一般形式，均值滤波求和后进行了归一化，而方框滤波可以选择是否归一化
//  另外增加了输出图像的深度选择

//  void cv::boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor = Point(-1, -1), bool normalize = true, int borderType = BORDER_DEFAULT)
//  相比均值滤波增加了的参数：
//  ddpeth: 输出图像的数据深度，赋值 -1 表示自动选择（一般来说输出图像的深度需要高于或者等于输入图像）
//  normalize: 默认为 true，即进行归一化

//  sqrBoxFilter() 函数把元素值“求和”，变成求“平方和”
//  注意：
//  由于 CV_8U 数据类型数值为 0～255，平方和后数据很大，即使归一化也有可能超过最大值
//  而 CV_32F 数据值是 0～1 的小数，所以平方后会很小，但结果依然在 0～1 范围
//  所以该函数只要用于 CV_32F 类型图像数据
//  由于归一化后数值会变小，即图片会变暗

void TestBoxFilter()
{
    // 读取图片
    cv::Mat lena = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please chech the image file!" << std::endl;
        return;
    }
    
    // 初始化一个矩阵
    float points[16] = {1,2,3,4,5,6,7,8,9,10,11,12};
    cv::Mat mat(4, 4, CV_32FC1, points);
    
    // 图片转换深度
    cv::Mat lena_32F;
    lena.convertTo(lena_32F, CV_32F, 1.0/255); // 第三个参数是 scale factor
    
    // 初始化结果存放空间
    cv::Mat result_mat_sqr, result_mat_sqr_norm, result_lena, result_lena_norm, result_lena_sqr, result_lena_sqr_norm;
    
    cv::boxFilter(lena, result_lena, -1, cv::Size(3,3), cv::Point(-1,-1), false);
    cv::boxFilter(lena, result_lena_norm, -1, cv::Size(3,3), cv::Point(-1,-1), true);
    
    cv::sqrBoxFilter(mat, result_mat_sqr, -1, cv::Size(3,3), cv::Point(-1,-1), false);
    cv::sqrBoxFilter(mat, result_mat_sqr_norm, -1, cv::Size(3,3), cv::Point(-1,-1), true);
    
    cv::sqrBoxFilter(lena_32F, result_lena_sqr, -1, cv::Size(3,3), cv::Point(-1,-1), false);
    cv::sqrBoxFilter(lena_32F, result_lena_sqr_norm, -1, cv::Size(3,3), cv::Point(-1,-1), true);
    
    // 打印结果矩阵
    std::cout << result_mat_sqr << std::endl;
    std::cout << result_mat_sqr_norm << std::endl;
    // 结果显示：
    // 没有归一化的很多值都超过了 255
    
    // 显示结果图像
    cv::imshow("origin lena", lena);
    cv::imshow("lena with box filter", result_lena);
    cv::imshow("lena with box filter and norm", result_lena_norm);
    cv::imshow("lena with sqrbox filter", result_lena_sqr);
    cv::imshow("lena with sqrbox filter and norm", result_lena_sqr_norm);
    // 结果显示：
    // 归一化是非常必要的，归一化后的滤波图和原图比较类似，而没有归一化的滤波图非常亮
    
    cv::waitKey(0);
    return;
}


//  5.3.3 高斯滤波
//  高斯噪声在图像采集中非常常见
//  高斯滤波器考虑了像素点和中心距离，滤波器中心位置为高斯分布均值
//  然后根据高斯分布公示和像素离开中心位置的距离，计算每个像素点的值

//  void cv::GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int aborderType = BORDER_DEFAULT)
//  输入图像可以是任意通道数，但类型必须是 CV_8U, CV_16U, CV_16S, CV_32F, CV_64F
//  ksize: 不同于别的滤波器，这里可以设置为 0，表示根据输入的标准差计算滤波器尺寸
//  sigmaX: X 方向的标准差
//  sigmaY: Y 方向的标准差，设置为 0 表示和 sigmaX 相等，两个轴都设为 0 表示根据高斯滤波器尺寸计算标准差
//  建议明确给出 ksize，sigmaX，sigmaY 以达到预期的滤波效果

//  在 opencv 中可以使用 getGaussianKernel() 函数，输入滤波器单一方向尺寸和标准差，生成单一方向高斯滤波器
//  注意，这个函数中 滤波器尺寸 和 标准差 的关系，并不等价于数学中的关系，而是 opencv 定义的关系

//  Mat cv::getGaussianKernel(int ksize, double sigma, int ktype = CV_64F)
//  ksize: 滤波器尺寸，必须为正数，奇数
//  sigma: 标准差，如果设置为负数，则会调用默认公式生成 sigma = 0.3((ksize-1)0.5-1+0.8)
//  ktype: 滤波器系数的数据类型，CV_32F 或 CV_64F，默认为 CV_64F
//  该函数输出的是一个 ksize*1 的 Mat 类矩阵
//  生成二维的高斯滤波器，需要调用两次该函数，将 X 方向和 Y 方向的高斯滤波器相乘
//  比如 X 和 Y 的尺寸为 3*1，则 X 乘以 Y 的转置，得到 3*3 的矩阵

void TestGaussFilter()
{
    // 读取图片
    cv::Mat lena = cv::imread("./data/lena.jpg");
    if (lena.empty())
    {
        std::cout << "Error, please chech the image file!" << std::endl;
        return;
    }
    
    // 调用 "noiseGeneration.hpp" 中的函数添加噪声
    cv::Mat lena_gauss_noise = AddGaussNoise(lena, 10, 20); // 添加高斯噪声，均值 10，标准差 20
    cv::Mat lena_salt_noise = AddSaltAndPepperNoise(lena, 10000); // 添加椒盐噪声，10000 个噪声点
    
    // 显示图像
    cv::imshow("origin lena", lena);
    cv::imshow("lena with gauss noise", lena_gauss_noise);
    cv::imshow("lena with salt noise", lena_salt_noise);
    
    // 初始化结果矩阵
    cv::Mat result_lena_k5, result_gauss_k5, result_salt_k5, result_lena_k9, result_gauss_k9, result_salt_k9;
    
    // 高斯滤波
    cv::GaussianBlur(lena, result_lena_k5, cv::Size(5,5), 10, 20);
    cv::GaussianBlur(lena_gauss_noise, result_gauss_k5, cv::Size(5,5), 10, 20);
    cv::GaussianBlur(lena_salt_noise, result_salt_k5, cv::Size(5,5), 10, 20);
    cv::GaussianBlur(lena, result_lena_k9, cv::Size(9,9), 10, 20);
    cv::GaussianBlur(lena_gauss_noise, result_gauss_k9, cv::Size(9,9), 10, 20);
    cv::GaussianBlur(lena_salt_noise, result_salt_k9, cv::Size(9,9), 10, 20);
    
    // 显示结果
    cv::imshow("lena after gauss blur (kernel 5*5)", result_lena_k5);
    cv::imshow("lena_gauss after gauss blur (kernel 5*5)", result_gauss_k5);
    cv::imshow("lena_salt after gauss blur (kernel 5*5)", result_salt_k5);
    cv::imshow("lena after gauss blur (kernel 9*9)", result_lena_k9);
    cv::imshow("lena_gauss after gauss blur (kernel 9*9)", result_gauss_k9);
    cv::imshow("lena_salt after gauss blur (kernel 9*9)", result_salt_k9);
    
    cv::waitKey(0);
    return;
}


//  5.3.4 可分离滤波
//  很多时候，滤波需要根据实际需求调整滤波器，比如设定非矩形的滤波器，又比如计算时不考虑原中心值
//  而利用 opencv 提供的卷积函数 filter2D()，我们就可以实现定制化的滤波器

//  并行计算
//  由于每一次滤波器和图像的计算都是独立的，即前面的计算不影响后面的计算，后面的计算不依赖于前面计算的结果
//  所以可以并行处理，即图像滤波是一个并行算法，提供并行计算的处理器可以大幅提升图像滤波速度

//  可分离性
//  可以先对 X 方向滤波，再对 Y 方向滤波，结果和同时对两个方向滤波相同
//  两个方向的滤波器联合矩阵相乘的到方阵， 3*1 乘以 1*3 得到 3*3

//  如果使用 filter2D()，要么先进行两个方向的滤波器联合，要么依次进行两个方向的滤波
//  替代方案是 sepFileter2D()，可以直接输入两个方向的滤波器

//  void cv::sepFilter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1,-1), double delta = 0, int borderType = BORDER_DEFAULT)
//  kernelX: X 方向的滤波器
//  kernelY: Y 方向的滤波器
//  delta: 偏置，计算结果会加上偏置
//  注意，这里滤波器尺寸可以是 K*1，也可以是 1*K，不影响滤波结果

void TestSepFilter()
{
    return;
}
