#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 利用感兴趣区域ROI实现图像叠加

bool LinearBlending() {
    // [0]定义一些局部变量
    double alphaValue = 0.5;
    double betaValue;
    
    Mat srcImage2, srcImage3, dstImage;
    
    // [1]读取图像(两幅图片需为同样的类型和尺寸)
    srcImage2 = imread("cat2.jpg");
    srcImage3 = imread("baboon2.jpg");
    
    if (!srcImage2.data) {
        printf("读取srcImage2错误~! \n");
        return false;
    }
    
    if (!srcImage3.data) {
        printf("读取srcImage3错误~! \n");
        return false;
    }
    
    // [2]做图像混合加权操作
    betaValue = (1.0 - alphaValue);
    addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);
    
    // [3]创建并显示原图窗口
    namedWindow("<2>线性混合示例窗口[原图]", 1);
    imshow("<2>线性混合窗口[原图]", srcImage2);
    
    namedWindow("<3>线性混合示例窗口[效果图]", 1);
    imshow("<3>线性混合示例窗口[效果图]", dstImage);
    
    return true;
}


int main(int argc, char** argv) {
    
    bool result = LinearBlending();
    
    waitKey(0);
    
    return 0;
    
}
