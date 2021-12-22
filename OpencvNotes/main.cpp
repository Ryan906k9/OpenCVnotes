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
    imageBasic1();
    /// 读取一副图片
//    src = imread(argv[1], 1 );
    src1 = imread("./data/fruits.jpg");
    src2 = src1;
    
    

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
