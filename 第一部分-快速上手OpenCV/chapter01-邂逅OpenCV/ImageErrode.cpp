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
    imshow("【原图】腐蚀操作", srcImage);
    
    // [3]进行腐蚀操作
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage;
    erode(srcImage, dstImage, element);
    // [4]显示效果图
    imshow("【效果图】腐蚀操作", dstImage);
    
    waitKey(6000);

    return 0;
}
