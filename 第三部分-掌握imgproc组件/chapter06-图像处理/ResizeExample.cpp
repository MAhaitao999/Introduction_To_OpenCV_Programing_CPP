#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <regex>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 载入原始图
    Mat srcImage = imread("cat.jpg");

    Mat tempImage, dstImage1, dstImage2; // 临时变量和目标图的定义
    tempImage = srcImage; // 将原始图赋给临时变量

    // 显示原始图
    imshow("[原始图]", srcImage);

    // 进行尺寸调整操作
    resize(tempImage, dstImage1, Size(tempImage.cols/2, tempImage.rows/2), (0, 0), (0, 0), 3);
    resize(tempImage, dstImage2, Size(tempImage.cols*2, tempImage.rows*2), (0, 0), (0, 0), 3);
    
    // 显示效果图
    imshow("[效果图之一]", dstImage1);
    imshow("[效果图之二]", dstImage2);
    waitKey(0);
   
    return 0;
    
}
