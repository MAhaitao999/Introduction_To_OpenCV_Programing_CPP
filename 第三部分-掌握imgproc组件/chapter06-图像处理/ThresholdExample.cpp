#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <regex>

using namespace std;
using namespace cv;

// 定义一些辅助宏
#define WINDOW_NAME "[程序窗口]"  // 为窗口标题定义的宏

// 全局变量声明
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

// 全局函数的声明
static void on_Threshold(int, void *); // 回调函数

int main(int argc, char** argv) {
    
    // [1] 载入原始图
    g_srcImage = imread("cat.jpg");

    if (!g_srcImage.data) {
        cout << "读取srcImage错误~! \n";
        return -1;
    }
    
    // [2] 保留一份原图的灰度图
    cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
    
    // [3] 创建窗口并显示原始图
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, g_srcImage);
    
    // [4]　创建滑动条来控制阈值
    createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
    createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
    
    // [5] 初始化自定义的阈值回调函数
    on_Threshold(0, 0);
    
    // [6] 轮询等待用户按键, 如果ESC键按下则退出程序
    while (1) {
        int key;
        key = waitKey(20);
        if ((char)key == 27) {break;}
    }
   
    return 0;
    
}

void on_Threshold(int, void*) {

    // 调用阈值函数
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    
    // 更新效果图
    imshow(WINDOW_NAME, g_dstImage);
}
