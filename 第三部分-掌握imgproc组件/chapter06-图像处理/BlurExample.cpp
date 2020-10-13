#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    Mat image = imread("face.jpg");
    
    // 创建窗口
    namedWindow("均值滤波[原图]");
    namedWindow("均值滤波[效果图]");
    
    // 显示原图
    imshow("均值滤波[原图]", image);
    
    // 进行滤波操作
    Mat out;
    blur(image, out, Size(7, 7));
    
    // 显示效果图
    imshow("均值滤波[效果图]", out);
    
    waitKey(0);
    
    return 0;
    
}
