#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <memory>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "[原始图窗口]"
#define WINDOW_NAME2 "[效果图窗口]"

// 描述: 全局变量的声明
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 100;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

// 描述: 全局函数的声明
void on_ThreshChange(int, void*);

int main(int argc, char** argv) {

    g_srcImage = imread("cat.jpg", 1);
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    blur(g_grayImage, g_grayImage, Size(3, 3));
    
    // 创建原图窗口并显示
    namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME1, g_srcImage);
    
    // 创建滚动条
    createTrackbar("阈值:", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
    on_ThreshChange(0, 0); // 调用一次进行初始化
    
    waitKey(0);
    
    return 0;
    
}

void on_ThreshChange(int, void*) {
    
    // 使用Canny边缘检测
    // cout << "Hello world" << g_nThresh << endl;
    Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3);
    // imshow(WINDOW_NAME2, g_cannyMat_output);
    
    // 找到轮廓
    findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    // 计算矩
    // cout << g_vContours[0] << endl;
    vector<Moments> mu(g_vContours.size());
    for (unsigned int i=0; i < g_vContours.size(); i++) {
        mu[i] = moments(g_vContours[i], false);
    }
    
    // 计算中心矩
    vector<Point2f> mc(g_vContours.size());
    for (unsigned int i=0; i < g_vContours.size(); i++) {
        mc[i] = Point2f(static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00));
    }
    
    // 绘制轮廓
    Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
    for (unsigned int i=0; i < g_vContours.size(); i++) {
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
        drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point()); // 绘制外层和内层轮廓
        circle(drawing, mc[i], 4, color, -1, 8, 0); // 绘制圆
    }
    
    // 显示到窗口
    namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME2, drawing);
    ;
    // 通过m00计算轮廓面积并且和OpenCV函数比较
    printf("\t输出内容: 面积和轮廓长度\n");
    for (unsigned int i=0; i < g_vContours.size(); i++) {
        printf(">通过m00计算出轮廓[%u]的面积: (M_00) = %.2f \n OpenCV函数计算出的面积=%.2f, 长度: %.2f \n\n", i, mu[i].m00, contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
        drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
        circle(drawing, mc[i], 4, color, -1, 8, 0);
    }
    
}
