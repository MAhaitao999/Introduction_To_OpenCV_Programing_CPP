#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 载入原图
    Mat srcImage = imread("baboon2.jpg");
    if (!srcImage.data) {
        printf("读取srcImage错误~!  \n");
        return false;
    }
    
    // 创建窗口
    namedWindow("[原始图]");
    namedWindow("[效果图]");
    
    // 显示原始图
    imshow("[原始图]", srcImage);
    
    // 定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    
    // 进行形态学操作
    // 1. 形态学梯度
    // morphologyEx(srcImage, srcImage, MORPH_GRADIENT, element); // 膨胀图与腐蚀图之差
    // 2. 开运算
    // morphologyEx(srcImage, srcImage, MORPH_OPEN, element);
    // 3. 闭运算
    // morphologyEx(srcImage, srcImage, MORPH_CLOSE, element);
    // 4. 顶帽
    // morphologyEx(srcImage, srcImage, MORPH_TOPHAT, element); // 原图与开运算之差
    // 5. 黑帽
    // morphologyEx(srcImage, srcImage, MORPH_BLACKHAT, element); // 闭运算与原图之差
    // 6. 腐蚀
    // morphologyEx(srcImage, srcImage, MORPH_ERODE, element);
    // 7. 膨胀
    morphologyEx(srcImage, srcImage, MORPH_DILATE, element);

    
    imshow("[效果图]", srcImage);
    
 
    while (char(waitKey(1)) != 'q') {}
    return 0;
    
}
