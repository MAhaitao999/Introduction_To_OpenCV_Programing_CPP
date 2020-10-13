#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 全局变量声明
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6;  // 方框滤波内核值
int g_nMeanBlurValue = 10;  // 均值滤波内核值
int g_nGaussianBlurValue = 6; // 高斯滤波内核值
int g_nMedianBlurValue = 10; // 中值滤波参数值
int g_nBilateralFilterValue = 10; // 双边滤波参数值

// 全局函数声明部分: 轨迹条回调函数
static void on_BoxFilter(int, void *);  // 方框滤波
static void on_MeanBlur(int, void *);  // 均值块滤波器
static void on_GaussianBlur(int, void *); // 高斯滤波器
static void on_MedianBlur(int, void *); // 中值滤波器
static void on_BilateralFilter(int, void *); // 双边滤波器

int main(int argc, char** argv) {
    
    // 载入原图
    Mat image = imread("cat.jpg");
    
    g_srcImage = imread("baboon2.jpg", 1);
    if (!g_srcImage.data) {
        printf("读取srcImage错误~! \n");
        return false;
    }
    
    // 复制原图到5个Mat类型中
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    g_dstImage4 = g_srcImage.clone();
    g_dstImage5 = g_srcImage.clone();
    
    // 显示原图
    namedWindow("[<0>原图窗口]", 1);
    imshow("[<0>原图窗口]", g_srcImage);
    
    // <1>方框滤波
    // 创建窗口
    namedWindow("[<1>方框滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<1>方框滤波]", &g_nBoxFilterValue, 50, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    
    // <2>均值滤波
    // 创建窗口
    namedWindow("[<2>均值滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<2>均值滤波]", &g_nMeanBlurValue, 50, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);
    
    // <3>高斯滤波
    // 创建窗口
    namedWindow("[<3>高斯滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<3>高斯滤波]", &g_nGaussianBlurValue, 50, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);

    // <4>中值滤波
    // 创建窗口
    namedWindow("[<4>中值滤波]", 1);
    // 创建轨迹条
    createTrackbar("参数值: ", "[<4>中值滤波]", &g_nMedianBlurValue, 50, on_MedianBlur);
    on_MedianBlur(g_nMedianBlurValue, 0);

    // <5>双边滤波
    // 创建窗口
    namedWindow("[<5>双边滤波]", 1);
    // 创建轨迹条
    createTrackbar("参数值: ", "[<5>双边滤波]", &g_nBilateralFilterValue, 50, on_BilateralFilter);
    on_BilateralFilter(g_nBilateralFilterValue, 0);
    
    while(char(waitKey(1)) != 'q') {}
    
    return 0;
    
}

// 方框滤波的回调函数
static void on_BoxFilter(int, void *) {
    // 方框滤波操作
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
    // 显示窗口
    imshow("[<1>方框滤波]", g_dstImage1);
}

static void on_MeanBlur(int, void *) {
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1, -1));
    imshow("[<2>均值滤波]", g_dstImage2);
}

static void on_GaussianBlur(int, void *) {
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
    imshow("[<3>高斯滤波]", g_dstImage3);
}

static void on_MedianBlur(int, void *) {
    medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1);
    imshow("[<4>中值滤波]", g_dstImage4);
}

static void on_BilateralFilter(int, void *) {
    bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
    imshow("[<5>双边滤波]", g_dstImage5);
}
