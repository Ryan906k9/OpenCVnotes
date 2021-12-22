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
    cv::Mat a26 = (cv::Mat_<double>(2, 2) << 1, 2, 3, 4);
    cv::Mat a27 = (cv::Mat_<double>(2, 2) << 4, 3, 2, 1);
    cv::Mat a28, a29;
    a28 = a26 + a27; // 对应元素相加
    // std::cout << a28 << std::endl;
    // [5, 5;
    // 5, 5]
    a29 = a26 - a27; // 对应元素相减
    // std::cout << a29 << std::endl;
    // [-3, -1;
    // 1, 3]
    
    cv::Mat a30 = (cv::Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);
    cv::Mat a31 = (cv::Mat_<double>(3, 2) << 6, 5, 4, 3, 2, 1);
    cv::Mat a32;
    a32 = a30 * a31; // 矩阵乘法，要求前一个矩阵的 列数 = 后一个矩阵的 行数
    // std::cout << a32 << std::endl;
    // [20, 14;
    // 56, 41]
    
    cv::Mat a33 = (cv::Mat_<double>(2, 3) << 6, 5, 4, 3, 2, 1);
    double a34;
    a34 = a30.dot(a33); // 两个矩阵被展开成向量，然后计算内积，返回的是 double 值
    // std::cout << a34 << std::endl;
    // 56
    // 注意，这里两个矩阵必须维度完全相同，仅仅保证展开成向量后长度相同是不够的！！！
    // 比如 a30 和 a31 计算 dot() 就会报错
    
    cv::Mat a35 = (cv::Mat_<double>(2, 3) << 2, 2, 2, 1, 1, 1);
    cv::Mat a36 = (cv::Mat_<double>(2, 3) << 2.1, 2, 2, 1.1, 1, 1);;
    cv::Mat a37;
    a37 = a36.mul(a35); // 对应元素相乘
    // std::cout << a37 << std::endl;
    // [4.2, 4, 4;
    //  1.1, 1, 1]
    // 注意：
    // 这里两个 Mat 内的元素类型，维度必须都相同！！！
    // 另外需要注意，相乘后超出类型的取值范围，数据溢出问题，比如图像输出超过 255 会输出 255
    
    // 2.1.4 Mat 元素读取
    // Mat 的存储方式：
    // 第1个元素的所有通道数据，第2个元素的所有通道数据。。。。
    // Mat 类变量常用属性：
    cv::Mat a38 = cv::Mat::ones(2, 2, CV_8UC3);
    // std::cout << "size: " << a38.size << std::endl;
    // size: 2 x 2
    // 维度
    // std::cout << "type(): " << a38.type() << std::endl;
    // type(): 16
    // 类型，CV_8U 类型为0，CV_8S 类型为1
    // std::cout << "cols: " << a38.cols << std::endl;
    // cols: 2
    // std::cout << "rows: " << a38.rows << std::endl;
    // rows: 2
    // std::cout << "step: " << a38.step << std::endl;
    // step: 6
    // 矩阵宽度（字节），这里一行 2 个元素 ，无符号整型，3 通道，即 2*1*3=6
    // 注：1个字节是8位，如果是32位的类型，则是4个字节
    // std::cout << "elemSize(): " << a38.elemSize() << std::endl;
    // elemSize(): 3
    // 每个元素大小（字节），一个元素 3 通道，无符号整型，即 3*1=3
    // std::cout << "total(): " << a38.total() << std::endl;
    // total(): 4
    // 元素个数
    // std::cout << "channels: " << a38.channels() << std::endl;
    // channels: 3
    // 通道数
    
    // 1. at 方法读取
    cv::Mat a39 = (cv::Mat_<uchar>(2, 2) << 1, 2, 3, 4);
    int a40 = (int)a39.at<uchar>(0, 1);
    // std::cout << a40 << std::endl;
    // 2
    // 注意：
    // at 后面的数据类型必须和矩阵元素的数据类型一致，否则会报错
    
    // 针对 3 通道，一个元素包含 3 个值，有专门的变量对应
    // cv::Vec3b, cv::Vec3s, cv::Vec3w, cv::Vec3d, cv::Vec3f, cv::Vec3i
    // 3 表示通道数，b表示uchar，s表示short，w表示ushort
    // d表示double，f表示float，i表示int
    // 2 通道和 4 通道只要替换对应的数字即可
    cv::Mat a41(3, 3, CV_8UC3, cv::Scalar(1, 2, 3));
    cv::Vec3b a42 = a41.at<cv::Vec3b>(1, 2); // 这里每个元素包含 3 个通道
    int first = (int)a42.val[0]; // 这里序号从 0 开始
    int second = (int)a42.val[1];
    int third = (int)a42.val[2];
    // std::cout << first << std::endl;
    // 1
    // std::cout << second << std::endl;
    // 2
    // std::cout << third << std::endl;
    // 3
    // 这里我的理解是 int 占4个字节32位，所以对应的是 CV_32S
    // uchar 对应 CV_8U 占1个字节8位，范围 0～255，一般图像数据在这个范围
    
    // 2. ptr 指针方法读取
    cv::Mat a43(3, 4, CV_8UC3, cv::Scalar(1, 2, 3));
    
    // 3. 迭代器读取
    
    // 4. 地址定位读取
    
}

// 2.2 图像读取，显示
void imageBasic2()
{
    
}
