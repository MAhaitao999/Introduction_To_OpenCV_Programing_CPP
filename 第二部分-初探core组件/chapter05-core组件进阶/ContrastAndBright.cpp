#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 全局函数声明
static void on_ContrastAndBright(int, void*);
static void ShowHelpText();

// 全局变量声明
int g_nContrastValue; // 对比度值
int g_nBrightValue;   // 亮度值
Mat g_srcImage, g_dstImage;

// 控制台应用程序的入口函数, 我们的程序从这里开始
int main(int argc, char** argv) {
    
    // [1]读取输入图像
    g_srcImage = imread("baboon2.jpg");
    if (!g_srcImage.data) {
        cout << "输入图片有误, 请确定目录下是否有imread函数指定图片存在~!" << endl;
        return false;
    }
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
    
    // [2]设定对比度和亮度的初值
    g_nContrastValue = 80;
    g_nBrightValue = 80;
    
    // [3]创建效果图窗口
    namedWindow("[效果图窗口]", 1);
    
    // [4]创建轨迹条
    createTrackbar("对比度: ", "[效果图窗口]", &g_nContrastValue, 300, on_ContrastAndBright);
    createTrackbar("亮 度: ", "[效果图窗口]", &g_nBrightValue, 200, on_ContrastAndBright);
    
    // [5]进行回调函数初始化
    on_ContrastAndBright(g_nContrastValue, 0);
    on_ContrastAndBright(g_nBrightValue, 0);
    
    // [6]按下"q"键, 程序退出
    while(char(waitKey(1)) != 'q') {}
    
    return 0;
    
}

static void on_ContrastAndBright(int, void*) {
    // 创建窗口
    namedWindow("[原始图窗口]", 1);
    // 三个for循环, 执行运算g_dstImage(i, j)=a*g_srcImage(i, j)+b
    for (int y=0; y < g_srcImage.rows; y++) {
        for (int x=0; x < g_srcImage.cols; x++) {
            for (int c=0; c < 3; c++) {
                g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
            }
        }
    }
    
    // 显示图像
    imshow("[原始图窗口]", g_srcImage);
    imshow("[效果图窗口]", g_dstImage);
}
