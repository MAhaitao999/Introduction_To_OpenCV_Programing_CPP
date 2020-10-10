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
    
    // [1]载入原图
    Mat srcImage = imread("/home/transwarp/Downloads/cat.jpg");
    
    // [2]显示原图
    imshow("【原图】均值滤波", srcImage);
    
    // [3]进行均值滤波操作
    Mat dstImage;
    blur(srcImage, dstImage, Size(7, 7));
    
    // [4]显示效果图
    imshow("【效果图】均值滤波", dstImage);
    
    waitKey(6000);

    return 0;
}
