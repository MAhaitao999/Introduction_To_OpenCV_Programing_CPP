#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <memory>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "[原始图]"
#define WINDOW_NAME2 "[修补后的效果图]"

// 描述: 全局变量的声明
Mat srcImage1, inpaintMask;
Point previousPoint(-1, -1); // 原来点的坐标

static void on_Mouse(int event, int x, int y, int flags, void*);

int main(int argc, char *argv[]) {

    // 载入原始图并进行掩膜的初始化
    Mat srcImage = imread("baboon2.jpg", -1);
    if (!srcImage.data) {
        printf("读取图片错误, 请确定目录下是否有imread函数指定图片存在~! \n");
        return -1;
    }
    
    srcImage1 = srcImage.clone();
    inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);
    
    // 显示原始图
    imshow(WINDOW_NAME1, srcImage1);
    
    // 设置鼠标回调消息
    setMouseCallback(WINDOW_NAME1, on_Mouse, 0);
    
    // 轮询按键, 根据不同的按键进行处理
    while (1) {
        // 获取按键键值
        char c = (char)waitKey();
        
        // 按键为ESC, 程序退出
        if (c == 27) {
            break;
        }
        
        // 键值为2, 恢复成原始图像
        if (c == '2') {
            inpaintMask = Scalar::all(0);
            srcImage.copyTo(srcImage1);
            imshow(WINDOW_NAME1, srcImage1);
        }
        
        // 键值为1或者空格, 进行图像修补操作
        if (c == '1' || c == ' ') {
            Mat inpaintedImage;
            inpaint(srcImage, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
            imshow(WINDOW_NAME2, inpaintedImage);
        }
    }
    
    return 0;
}

// 鼠标消息回调函数
static void on_Mouse(int event, int x, int y, int flags, void*) {
    
    // 处理鼠标左键相关信息
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        previousPoint = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        previousPoint = Point(x, y);
    
    // 鼠标左键按下并移动, 进行绘制
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        Point pt(x, y);
        if (previousPoint.x < 0) {
            previousPoint = pt;
        }
        // 绘制白色线条
        line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
        line(srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0);
        previousPoint = pt;
        imshow(WINDOW_NAME1, srcImage1);
    }
}
