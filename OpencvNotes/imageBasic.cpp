//
//  imageBasic.cpp
//  OpencvNotes
//  第二章 数据载入，显示，保存
//  Created by Ray on 2021/12/21.
//
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/gapi/own/types.hpp>
#include "imageBasic.hpp"
#include <iostream>

//using namespace std;

// 2.1 存储图像的容器
void ImageBasic1()
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
    // 矩阵有 2 列
    // std::cout << "rows: " << a38.rows << std::endl;
    // rows: 2
    // 矩阵有 2 行
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
    std::cout << a40 << std::endl;
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
    std::cout << first << std::endl;
    // 1
    std::cout << second << std::endl;
    // 2
    std::cout << third << std::endl;
    // 3
    // 这里我的理解是 int 占4个字节32位，所以对应的是 CV_32S
    // uchar 对应 CV_8U 占1个字节8位，范围 0～255，一般图像数据在这个范围
    
    // 2. ptr 指针方法读取
    cv::Mat a43(3, 4, CV_8UC3, cv::Scalar(1, 2, 3));
    for (int i = 0; i < a43.rows; i++) // 遍历矩阵的行
    {
        uchar* ptr = a43.ptr<uchar>(i); // 获得对应行的开头地址（指针）
        for (int j = 0; j < a43.cols * a43.channels(); j++) // 遍历列
        {
            std::cout << (int)ptr[j] << std::endl; // 每次 j 向后移动一个字节
        }
    }
    // 注意：
    // 这里取行的时候，需要指定元素类型 <uchar>，使用圆括号
    // 在行中遍历元素的时候，需要用方括号
    // 始终要记住，这里存储数据是一个元素的多个通道都存好了，再下一个元素这样的顺序！
    
    std::cout << (int)a43.ptr<uchar>(2)[4] << std::endl;
    // 也可以直接读取对应行列序号对应的值，这里超出范围编译不会报错，所以要注意！
    
    // 3. 迭代器读取
    // Mat 类的变量是容器变量，所以拥有迭代器
    cv::MatIterator_<cv::Vec3b> it = a43.begin<cv::Vec3b>();
    cv::MatIterator_<cv::Vec3b> it_end = a43.end<cv::Vec3b>();
    for (int i = 0; it != it_end; it++)
    {
        std::cout << (cv::Vec3b)(*it);
        if ((++i % a43.cols) == 0)
        {
            std::cout << std::endl;
        }
    }
    // 输出结果：
    // [1, 2, 3][1, 2, 3][1, 2, 3][1, 2, 3]
    // [1, 2, 3][1, 2, 3][1, 2, 3][1, 2, 3]
    // [1, 2, 3][1, 2, 3][1, 2, 3][1, 2, 3]
    
    // 注意，这里大多数的教学课程里面有个错误
    cv::MatIterator_<uchar> it2 = a43.begin<uchar>();
    cv::MatIterator_<uchar> it2_end = a43.end<uchar>();
    for (int i = 0; it2 != it2_end; it2++)
    {
        std::cout << (int)(*it2);
        if ((++i % a43.cols) == 0)
        {
            std::cout << std::endl;
        }
    }
    // 输出结果：
    // 1111
    // 1111
    // 1111
    
    // 4. 地址定位读取
    int a44;
    int row_index = 2, col_index = 3, channel_index = 2;
    a44 = (int)(*(a43.data + a43.step[0] * row_index + a43.step[1] * col_index + channel_index));
    std::cout << a44 <<std::endl;
    // 输出：
    // 3
    // 表示第 3 行，第 4 列， 第 3 通道的值
    // 注意：
    // step[i]: 表示每一维元素的大小，单位字节
    // step[0]: 表示第一维，即一行元素的大小，即矩阵宽度
    // step[1]: 表示第二维，即一个元素的大小，即通道数（元素宽度）
}

// 2.2 图像读取，显示
void ImageBasic2()
{
//    2.2.1 图像读取 imread
//    cv::Mat cv::imread(const String & filename, int flags = IMREAD_COLOR)
    cv::Mat image1 = cv::imread("./aero881.jpg", 0); // 该图片不存在
    if (image1.empty())
    {
        std::cout << "error" << std::endl;
    }
//    图片不存在，或者错误，empty() 的值为 1，否则为 0
    image1 = cv::imread("./data/aero1.jpg", 0);
    if (image1.empty())
    {
        std::cout << "error" << std::endl;
    } else {
        std::cout << "get" << std::endl;
    }
//    falgs标识位：
//    一共有 13 种，可用 "|" 声明多个（不冲突情况下）
//    enum      cv::ImreadModes {
//      cv::IMREAD_UNCHANGED = -1, 保留 Alpha 通道
//      cv::IMREAD_GRAYSCALE = 0, 转为单通道灰度图
//      cv::IMREAD_COLOR = 1, 转为 3 通道 BGR
//      cv::IMREAD_ANYDEPTH = 2, 保留原深度（16位/32位），默认转为 8位
//      cv::IMREAD_ANYCOLOR = 4, 以任意可能的颜色读取
//      cv::IMREAD_LOAD_GDAL = 8, 使用 gdal 驱动加载图像
//      cv::IMREAD_REDUCED_GRAYSCALE_2 = 16, 转灰度，缩小为 1/2
//      cv::IMREAD_REDUCED_COLOR_2 = 17, 转3通道，缩小为 1/2
//      cv::IMREAD_REDUCED_GRAYSCALE_4 = 32, 转灰度，缩小为 1/4
//      cv::IMREAD_REDUCED_COLOR_4 = 33, 转3通道，缩小为 1/4
//      cv::IMREAD_REDUCED_GRAYSCALE_8 = 64, 转灰度，缩小为 1/8
//      cv::IMREAD_REDUCED_COLOR_8 = 65, 转3通道，缩小为 1/8
//      cv::IMREAD_IGNORE_ORIENTATION = 128 不以 EXIF 方向旋转
//    }
//    注意：
//    读取不同格式图片需要对应的图片解码器
//    windows 和 mac 中 opencv 一般都带有：libjpeg, libpng, libtiff, libjasper
//    可以读取 jpg, jpeg, jpe, png, tiff, tif 后缀的图片
//    linux 中需要自行安装解码器
//    另外：
//    能否读取图片，还是看图片的格式，不是后缀，比如后缀 .png 的图片改成 .exe，依然可以被解码读取
//    另外：默认图像像素数小于 2^30，如果超过，需要修改系统变量 OPENCV_IO_MAX_IMAGE_PIXELS
    
//    2.2.2 图像窗口 namedWindow
//    void cv::namedWindow(const String & winname, int flags = WINDOW_AUTOSIZE)
    cv::namedWindow("my first image", 1);
//    flags 标识：
//    一共 8 种，可用 "|" 声明多个（不冲突情况下）
//    enum      cv::WindowFlags {
//      cv::WINDOW_NORMAL = 0x00000000, 允许用户随意调整窗口大小
//      cv::WINDOW_AUTOSIZE = 0x00000001, 根据图像大小设定窗口大小，用户无法调整
//      cv::WINDOW_OPENGL = 0x00001000, 创建支持 OpenGL 的窗口
//      cv::WINDOW_FULLSCREEN = 1, 全屏显示
//      cv::WINDOW_FREERATIO = 0x00000100, 调整图像尺寸去满足窗口
//      cv::WINDOW_KEEPRATIO = 0x00000000, 保持图像比例
//      cv::WINDOW_GUI_EXPANDED =0x00000000, 窗口允许添加工具栏和状态栏
//      cv::WINDOW_GUI_NORMAL = 0x00000010 没有工具栏和状态栏的窗口
//    }
//    默认加载标识为："WINDOW_AUTOSIZE | WINDOW_KEEPRATIO | WINDOW_GUI_EXPANDED"
    
//    注意：
//    如果已经有同名窗口，不执行操作
//    窗口会占用内存，请在不需要的时候关闭以释放内存：cv::destroyWindow() 和 cv::destroyAllWindows()
//    另外：不知道是否 Mac 系统的原因，设置了 WINDOW_AUTOSIZE 后依然可以拖拽改变窗口大小！
//    看上面的 8 种情况，如果 flag 设置为 1，其实等同于 0x00000001，即 WINDOW_AUTOSIZE
//    所以这里虽然有 8 种，但是我估计是 opencv 开发团队进行的预留，其实还没开发完成。
    
//    2.2.3 显示图像 imshow
//    void cv::imshow(const String & winname, InputArray mat)
    cv::imshow("my first image", image1);
//    这里必须设置 waitKey()，否则 imshow 的执行后会直接关闭，用户看不到执行结果
    cv::waitKey(0);
//  waitKey() 的输入值为以毫秒计数的等待时长，如果设置为 0，则表示等到用户按键才结束
    
    
}

//    2.3 加载视频，调用摄像头
void ImageBasic3()
{
//    2.3.1 读取视频数据
//    使用 VideoCapture 类
//    cv::VideoCapture::VideoCapture(); // 默认的构造函数
//    cv::VideoCapture::VideoCapture(const String & filename, int apiPreference = CAP_ANY);
//    第二种构造函数可以读取：视频文件，图像序列，视频流 URL
//    图像序列要求格式：“前缀+数字”，调用格式：“前缀+%02d”
//    比如 image_00.jpg, image_01.jpg, image_02.jpg，加载时用 image_%02d.jpg
//    是否读取文件成功，可以通过 isOpened() 函数判断，成功返回 true
    
//    通过 >> 操作符，可以将视频类变量 VideoCapture 赋值给图像类 Mat
//    所有视频数据都赋值完成后，再进行赋值会为空，可以用 empty() 判断是否赋值完成
    
//    我们可以用 VideoCapture 变量的 get() 函数查看视频的属性
//    cv::VideoCapture::get(int propId)
//    多达 56 种属性，详情可以查阅 opencv document
//    常用的有：
//    cv::CAP_PROP_POS_MSEC =0, 视频文件当前位置（毫秒）
//    cv::CAP_PROP_POS_FRAMES =1, 下一帧的序号（0开始）
//    cv::CAP_PROP_POS_AVI_RATIO =2, 视频相对位置（0=开始，1=结束）
//    cv::CAP_PROP_FRAME_WIDTH =3, 视频图像宽度
//    cv::CAP_PROP_FRAME_HEIGHT =4, 视频图像高度
//    cv::CAP_PROP_FPS =5, 视频帧率（x帧/秒）
//    cv::CAP_PROP_FOURCC =6, 视频解码器的 4 位代码
//    cv::CAP_PROP_FRAME_COUNT =7, 视频的总帧数
//    cv::CAP_PROP_FORMAT =8, Mat 对象的格式，比如 CV_16SC3
//    cv::CAP_PROP_MODE =9, 指示当前捕捉模式（后端指定）
//    cv::CAP_PROP_BRIGHTNESS =10, 图像亮度（仅适用于支持的相机）
//    cv::CAP_PROP_CONTRAST =11, 图像对比度（仅适用于相机）
//    cv::CAP_PROP_SATURATION =12, 图像饱和度（仅适用于相机）
//    cv::CAP_PROP_HUE =13, 图像色调（仅适用于相机）
//    cv::CAP_PROP_GAIN =14, 图像增益（仅适用于支持的相机）
    
    cv::VideoCapture video1("./data/Megamind.avi");
    if (video1.isOpened())
    {
        std::cout << "width: " << video1.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
        std::cout << "height: " << video1.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
        std::cout << "FPS: " << video1.get(cv::CAP_PROP_FPS) << std::endl;
        std::cout << "frames: " << video1.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
//    width: 720
//    height: 528
//    FPS: 23.976
//    frames: 270
    }
    else
    {
        std::cout << "Error, please check the video file!" << std::endl;
    }
    while(true)
    {
        cv::Mat single_frame;
        video1 >> single_frame;
        if (single_frame.empty())
        {
            break;
        }
        cv::imshow("video images", single_frame);
        cv::waitKey(1000 / video1.get(cv::CAP_PROP_FPS));
        // FPS 帧率表示每秒（1000毫米）显示几帧
        // 所以 1000/FPS 表示每一帧图片展示的时间，即切换图片的时间
        // 这样展示图片就可以按照原来视频的速度进行播放了！
    }
    cv::waitKey();
    
//    2.3.2 调用摄像头
//    cv::VideoCapture::VideoCapture(int index, int apiPreference = CAP_ANY)
    cv::VideoCapture video2(0);
//    这里的 0 表示摄像头的 ID（从0开始）
    if (video2.isOpened())
    {
        std::cout << "width: " << video2.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
        std::cout << "height: " << video2.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
        std::cout << "FPS: " << video2.get(cv::CAP_PROP_FPS) << std::endl;
        std::cout << "frames: " << video2.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
//    width: 1280
//    height: 720
//    FPS: nan 摄像头捕捉的视频没有FPS
//    frames: 0 也不会有总的帧数
    }
    else
    {
        std::cout << "Error, please check the camera!" << std::endl;
    }
    while(true)
    {
        cv::Mat cam_frame;
        video2 >> cam_frame;
        cv::imshow("camera images", cam_frame);
        int k;
        k = cv::waitKey(10);
        // 1000/FPS=10 表示每一帧图片展示的时间，即 FPS=100
        if ((char)k == 27) // ASCII码为27的键（esc键）
        {
            break;
        }
    }
    
    return;
}

//    2.4 保存数据
//    2.4.1  保存图片
void SaveImage()
{
//    使用 imwrite() 函数
//    bool cv::imwrite(const String & filename, InputArray img, const std::vector<int>& params = std::vector<int>())
//    保存成功返回 true
//    通常保存的是 8 位单通道/3通道BGR彩色图片
//    设定不同图片后缀可以对应不同的 图像位数：
//    16 位无符号（CV_16U），保存为 png, jpeg, tiff
//    32 位浮点（CV_32F)，保存为 pfm, tiff, OpenEXR, Radiance HDR
//    4 通道（包含 Alpha 通道），保存为 png
    
    cv::Mat mat(480, 640, CV_8UC4); // 创建包含 alpha 通道的矩阵
    //
    // 以下部分在 opencv 官方案例中被包成了一个单独的函数 paintAlphaMat，用于生成一个渐变色的图片（包含BGRA这四个通道）
    //
    CV_Assert(mat.channels()  == 4);
    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols; ++j)
        {
            cv::Vec4b& bgra = mat.at<cv::Vec4b>(i, j); // 取得一个像素点的所有通道
            bgra[0] = UCHAR_MAX; // Blue
            bgra[1] = cv::saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX); // Green
            bgra[2] = cv::saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); // Red
            bgra[3] = cv::saturate_cast<uchar>(0.5 * (bgra[1] + bgra[2])); // Alpha
        }
    }
    //
    //
    //
    // 以下部分用于设置 imwrite() 的第三个参数
    std::vector<int> compression_params; // 需要是一个 vector<int>，包含2个元素
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION); // 第一个元素是标志，表示要改什么
    // 这里表示 PNG 的压缩
    compression_params.push_back(9); // 第二个元素是标志参数，表示要改到什么程度
    // 这里表示 PNG 最高的压缩级别
//    可选标志：
//    官方文档中罗列了 19 种，常见的如下
//    IMWRITE_JPEG_QUALITY // 设定 JPEG 的图片质量，0～100，默认 95
//    IMWRITE_JPEG_PROGRESSIVE // 增强 JPEG，0/1，默认 false
//    IMWRITE_JPEG_OPTIMIZE // 优化 JPEG，0/1，默认 false
//    IMWRITE_JPEG_LUMA_QUALITY // JPEG 分离的亮度质量等级，0～100，默认0（不使用）
//    IMWRITE_JPEG_CHROMA_QUALITY // JPEG 单独的色度质量等级，0～100，默认0
//    IMWRITE_PNG_COMPRESSION // PNG 的压缩级别，0～9，默认 1
//    IMWRITE_TIFF_COMPRESSION // TIFF 的压缩方案，可参考 libtiff，CV_32F 图像默认使用 SGILOG 模式，其他默认 LZW 模式

    bool result = false; // 初始化结果
    try
    {
        result = cv::imwrite("./alpha.png", mat, compression_params);
        // 写入图片，成功后返回值为 true
    }
    catch (const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (result)
        printf("Saved PNG file with alpha data.\n");
    else
        printf("ERROR: Can't save PNG file.\n");
    
    std::vector<cv::Mat> imgs; // 创建一个向量存放 Mat
    imgs.push_back(mat);
    imgs.push_back(~mat);
    imgs.push_back(mat(cv::Rect(0, 0, mat.cols / 2, mat.rows / 2)));
    cv::imwrite("./test.tiff", imgs); // 将多张图片存放到 tiff 文件
    printf("Multiple files saved in test.tiff\n");

}

//    2.4.2  保存视频
void SaveVideo()
{
//    使用 VideoWrite() 类
//    可以用于保存多幅图片生成的视频，或者摄像头拍摄到的视频
//    cv::VideoWriter::VideoWriter(); // 默认构造函数
//    cv::VideoWriter::VideoWriter(const String & filename, int fourcc, double fps, Size frameSize, bool isColor=true)
    
//    通过默认构造函数，可以创建一个数据流，
//    然后通过 open() 函数设置保存的文件名，编码器，帧数等参数
    
//    第二种构造函数中，fourcc 为 4 字符的视频编码器代码
//    查询网址：https://www.fourcc.org/codecs.php
//    常用编码器如下：
//    VideoWriter::fourcc('D','I','V','X') // 流行的 MPEG-4 编码
//    VideoWriter::fourcc('M','J','P','G') // 动态 JPEG 编码
//    VideoWriter::fourcc('I','2','6','3') // Intel 实现的 H.263 编码
    
    cv::Mat src;
    // 使用默认摄像头捕捉
    cv::VideoCapture cap(0);
    // 检查是否成功开启摄像头
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return;
    }
    
    // 获取一帧数据，以了解其大小和类型
    cap >> src;
    // 检测是否获取成功
    if (src.empty()) {
        std::cerr << "ERROR! blank frame grabbed\n";
        return;
    }
    
    bool isColor = (src.type() == CV_8UC3);
    // isColor 标志用于设定保存视频是否为彩色视频 true/false
    // 这里检测摄像头捕捉到的数据是不是 3 通道的，如果是，即为彩色视频
    //--- 初始化 VIDEOWRITER
    cv::VideoWriter writer; // 实力化类对象
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');  // 选择编码器 (在运行的时候需要是可用的)
    double fps = 25.0;                          // 设置帧率
    std::string filename = "./live.avi";             // 文件名
    writer.open(filename, codec, fps, src.size(), isColor);
    // 检查是否成功
    if (!writer.isOpened()) {
        std::cerr << "Could not open the output video file for write\n";
        return;
    }
    
    //--- 抓取和写入的循环
    std::cout << "Writing videofile: " << filename << std::endl
         << "Press any key to terminate" << std::endl;
    for (;;)
    {
        // 这里通过 VideoCapture::read() 函数来进行视频帧的抓取
        if (!cap.read(src)) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // 抓取的数据会存放到 src 中，同时返回一个是否抓取成功的标志 true/false
        // 如果抓取了一个空白帧，则返回 false，然后中断循环
        
        // 把帧数据编码成视频流
        writer.write(src);

        // 展示摄像头的实时画面
        cv::imshow("Live", src);
        // 如果侦测到按键行为，则跳出循环，即停止录制
        if (cv::waitKey(5) >= 0)
            break;
    }
    // VideoWriter 结构后，视频文件自动被关闭并释放
}

//    2.4.3 对 XML 和 YMAL 文件读取和保存
void TestXMLandXMAL()
{
//    图像之外的 Mat 矩阵，数组，字符串等数据，可以保存为 XML 和 YMAL
//    XML 是元标记语言，用户可以自定义标记，数据含义，隶属关系等，扩展名是 .xml
//    YMAL 是数据为中心的语言，定义数据的方式：“变量:数值”，用缩紧代表隶属关系，扩展名为 .yml 或者 .ymal
    
//    使用 FileStorage 类完成 XML 和 YMAL 的读写
//    cv::FileStorage::FileStorage(const String & filename, int flags, const String & encoding = String())
//    文件名参数要包含后缀 .xml .yml .ymal
    
//    操作类型标志：
//    READ = 0, // 读取
//    WRITE = 1, // 写入（覆盖原数据）
//    APPEND = 2, // 继续写入
//    MEMORY = 4, // 写入/读取到内部缓冲区
    
//    编码参数：
//    当前 UTF-16 XML 不支持，仅可使用 8-bit 编码 UTF-8 XML
    
//    通过 open() 函数打开文件，打开成功返回 true
//    通过 << 操作写入文件，比如 file << "price" << 18
//        数组用 "[]"， file << "price" << "[" << 18 << 24 << "]"
//        隶属关系用 "{}"， file << "price" << "{"<<"a"<<7<<"b"<<8<<"}"
//    通过 >> 操作读取文件，比如 file["price"] >> priceValue
//        通过定义 file["price"] 的 FileNode 节点类型变量
//        再进行对应寻址 FileNode["a"]
//    通过 write() 函数写入文件
//    可以写入类型：
//    int, double, String, Mat, vector<String>
    
//    system("color F0"); // 修改运行程序背景和文字颜色
    // Mac 下该指令无效，Linux 应该也是无效的，因为使用的是 termimal 命令
    
//    std::string fileName = "testXML.xml";
    std::string fileName = "testYAML.yaml"; // 根据后缀名存储成对应格式
    cv::FileStorage fileToWrite(fileName, cv::FileStorage::WRITE); // 以写入模式打开文件
    // 存入 Mat
    cv::Mat mat = cv::Mat::ones(3, 3, CV_8U);
    fileToWrite.write("mat", mat);
    // 存入浮点数
    float f = 10.1;
    fileToWrite << "float" << f;
    // 存入字符串
    std::string s = "great";
    fileToWrite << "string" << s;
    // 存入数组
    fileToWrite << "array" << "[" << 1 << 3 << 8 << "]";
    // 存入多节点数据
    fileToWrite << "Jack" << "{" << "age" << 18 << "time" << "[" << 1 << 45 << 36 << "]" << "}";

    fileToWrite.release(); // 关闭文件
    
    cv::FileStorage fileToRead(fileName, cv::FileStorage::READ); // 打开文件
    // 判断是否打开成功
    if (!fileToRead.isOpened())
    {
        std::cout << "Error! Check the file!" << std::endl;
    }
    
    // 读取浮点数
    float fRead;
    fileToRead["float"] >> fRead;
    std::cout << "float: " << fRead << std::endl;
    
    // 读取字符串
    std::string sRead;
    sRead = (std::string)fileToRead["string"];
    // 用等号 = 赋值，必须指明数据类型 (std::string)
    std::cout << "string: " << sRead << std::endl;
    
    // 读取数组（含有多数据的节点）
    cv::FileNode fileNode = fileToRead["array"];
    std::cout << "array: ";
    // 循环遍历读取
    for (cv::FileNodeIterator i = fileNode.begin(); i != fileNode.end(); ++i)
    {
        int x;
        *i >> x;
        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    // 读取 Mat 矩阵
    cv::Mat mRead;
    fileToRead["mat"] >> mRead;
    std::cout << "mat: " << mRead << std::endl;
    
    // 读取隶属关系的结构
    cv::FileNode fileNode1 = fileToRead["Jack"];
    int age = fileNode1["age"];
    std::cout << "Jack:" << std::endl
    << "age: " << age << std::endl;
    std::cout << "time: ";
    for (int i = 0; i < 3; i++)
    {
        int y = (int)fileNode1["time"][i];
        std::cout << y;
        if (i==2)
        {
            break;
        }
        std::cout << ":";
    }
    std::cout << std::endl;
    // 关闭文件
    fileToRead.release();
}
