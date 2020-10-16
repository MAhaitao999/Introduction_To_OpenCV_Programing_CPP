#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <regex>

using namespace std;
using namespace cv;

// 全局变量声明
// 原图, 原图的灰度版, 目标图
Mat g_srcImage, g_srcGrayImage, g_dstImage;

// Canny边缘检测相关变量
Mat g_cannyDetectionEdges;
int g_cannyLowThreshold = 1;  // TrackBar位置参数

// Sobel边缘检测相关变量
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1; // TrackBar位置参数

// Scharr滤波器相关变量
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

// 全局函数声明
static void on_Canny(int, void*); // Canny边缘检测窗口滚动条的回调函数
static void on_Sobel(int, void*); // Sobel边缘检测窗口滚动条的回调函数
void Scharr(); // 封装了Scharr边缘检测相关代码的函数

int main(int argc, char** argv) {
    
    g_srcImage = imread("cat.jpg");
    if (!g_srcImage.data) {
        printf("读取srcImage错误~! \n");
        return -1;
    }
    
    // 显示原始图
    namedWindow("[原始图]");
    imshow("[原始图]", g_srcImage);
    
    // 创建与src同类型和大小的矩阵(dst)
    g_dstImage.create(g_srcImage.size(), g_srcImage.type());
    
    // 将原图像转换为灰度图像
    cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
    
    // 创建显示窗口
    namedWindow("[效果图]Canny边缘检测", WINDOW_AUTOSIZE);
    namedWindow("[效果图]Sobel边缘检测", WINDOW_AUTOSIZE);
    
    // 创建trackbar
    createTrackbar("参数值: ", "[效果图]Canny边缘检测", &g_cannyLowThreshold, 120, on_Canny);
    createTrackbar("参数值: ", "[效果图]Sobel边缘检测", &g_sobelKernelSize, 3, on_Sobel);
    
    // 调用回调函数
    on_Canny(0, 0);
    on_Sobel(0, 0);
    
    // 调用封装了Scharr边缘检测代码的函数
    Scharr();
    
    // 轮询获取按键信息, 若按下Q, 程序退出
    while ((char(waitKey(1)) != 'q')) {}
   
    return 0;
    
}

void on_Canny(int, void*) {
    // 先使用3x3内核来降噪
    blur(g_srcGrayImage, g_cannyDetectionEdges, Size(3, 3));
    
    // 运行我们的Canny算子
    Canny(g_cannyDetectionEdges, g_cannyDetectionEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3);
    
    // 现将g_dstImage内的所有元素设置为0
    g_dstImage = Scalar::all(0);
    
    // 使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码, 来将原图g_srcImage拷贝到目标图g_dstImage中
    g_srcImage.copyTo(g_dstImage, g_cannyDetectionEdges);
    
    // 显示效果图
    imshow("[效果图]Canny边缘检测", g_dstImage);
}

void on_Sobel(int, void*) {
    // 求X方向梯度
    Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X); // 计算绝对值, 并将结果转换成8位
    
    // 求Y方向梯度
    Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y); // 计算绝对值, 并将结果转换成8位
    
    // 合并梯度
    addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);
    
    // 显示效果图
    imshow("[效果图]Sobel边缘检测", g_dstImage);
    
}

void Scharr() {
    // 求X方向梯度
    Scharr(g_srcImage, g_scharrAbsGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(g_scharrAbsGradient_X, g_scharrGradient_X); // 计算绝对值, 并将结果转换成8位
    
    // 求Y方向梯度
    Scharr(g_srcImage, g_scharrAbsGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(g_scharrAbsGradient_Y, g_scharrGradient_Y); // 计算绝对值, 并将结果转换成8位
    
    // 合并梯度
    addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);
    
    // 显示效果图
    imshow("[效果图]Scharr滤波器", g_dstImage);
}
