#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
/*
 * 
 */
int main(int argc, char** argv) {
    
    // [1]读入原始图片
    Mat srcImage = imread("/home/transwarp/Downloads/cat.jpg");
    
    // [2]显示原始图片
    imshow("【原始图】Canny边缘检测", srcImage);
    Mat dstImage, edge, grayImage; // 参数定义
    
    // [3]创建与src同类型和大小的矩阵(dst)
    dstImage.create(srcImage.size(), srcImage.type());
    
    // [4]将原图像转化为灰度图像
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
    
    // [5]先使用3x3内核来降噪
    blur(grayImage, edge, Size(3, 3));
    
    // [6]运行Canny算子
    Canny(edge, edge, 3, 9, 3);
    
    // [7]显示效果图
    imshow("【效果图】Canny边缘检测", edge);
    
    waitKey(0);

    return 0;
}
