#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 全局变量声明
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3; // 存储图片的Mat类型
int g_nBoxFilterValue=3; // 方框滤波参数值
int g_nMeanBlurValue=3; // 均值滤波器参数
int g_nGaussianBlurValue=3; // 高斯滤波参数值

// 全局函数声明: 轨迹条的回调函数
static void on_BoxFilter(int, void *); // 方框滤波
static void on_MeanBlur(int, void *); // 均值滤波
static void on_GaussianBlur(int, void *); // 高斯滤波

int main(int argc, char** argv) {
    
    // 载入原图
    g_srcImage = imread("cat.jpg", 1);
    if (!g_srcImage.data) {
        printf("读取srcImage错误~! \n");
        return false;
    }
    // 复制原图到三个Mat类型中
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    
    // 显示原图
    namedWindow("[<0>原图窗口]", 1);
    imshow("[<0>原图窗口]", g_srcImage);
    
    // [<1>方框滤波]
    // 创建窗口
    namedWindow("[<1>方框滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<1>方框滤波]", &g_nBoxFilterValue, 40, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    
    // [<2>均值滤波]
    // 创建窗口
    namedWindow("[<2>均值滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<2>均值滤波]", &g_nMeanBlurValue, 40, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);
    
    // [<3>高斯滤波]
    // 创建窗口
    namedWindow("[<3>高斯滤波]", 1);
    // 创建轨迹条
    createTrackbar("内核值: ", "[<3>高斯滤波]", &g_nGaussianBlurValue, 40, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);
    
    // 输出一些帮助信息
    cout << endl << "\t, 请调整滚动条观察图像效果~\n\n"
            << "\t按下`q`键时, 程序退出~!\n";
    
    // 按下`q`键时, 程序退出
    while(char(waitKey(1)) != 'q') {}
    
    waitKey(0);
    
    return 0;
    
}

// 描述: 方框滤波操作的回调函数
static void on_BoxFilter(int, void *) {
    // 方框滤波操作
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
    // 显示窗口
    imshow("[<1>方框滤波]", g_dstImage1);
}

static void on_MeanBlur(int, void *) {
    // 均值滤波操作
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1, -1));
    // 显示窗口
    imshow("[<2>均值滤波]", g_dstImage2);
}

static void on_GaussianBlur(int, void *) {
    // 高斯滤波操作
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
    // 显示窗口
    imshow("[<3>高斯滤波]", g_dstImage3);
}
