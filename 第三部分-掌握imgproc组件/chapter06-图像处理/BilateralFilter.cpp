#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 载入原图
    Mat image = imread("cat.jpg");
    
    // 创建窗口
    namedWindow("双边滤波[原图]");
    namedWindow("双边滤波[效果图]");
    
    // 显示原图
    imshow("双边滤波[原图]", image);
    
    // 进行双边滤波操作
    Mat out;
    bilateralFilter(image, out, 25, 25*2, 25/2);
    
    // 显示效果图
    imshow("双边滤波[效果图]", out);
    
    waitKey(0);
    
    return 0;
    
}
