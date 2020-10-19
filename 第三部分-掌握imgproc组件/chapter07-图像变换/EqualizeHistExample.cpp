#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
 
    // [1] 加载源图像
    Mat srcImage, dstImage;
    srcImage = imread("jianzhu.png", 1);
    if (!srcImage.data) {
        printf("读取图片错误, 请确定目录下是否有imread函数指定图片的存在~! \n");
        return false;
    }
    
    // [2] 转换为灰度图并显示出来
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
    imshow("原始图", srcImage);
    
    // [3] 进行直方图均衡化
    equalizeHist(srcImage, dstImage);
    
    // [4] 显示结果
    imshow("经过直方图均衡化后的图", dstImage);
    
    waitKey(0);
    
    return 0;
    
}
