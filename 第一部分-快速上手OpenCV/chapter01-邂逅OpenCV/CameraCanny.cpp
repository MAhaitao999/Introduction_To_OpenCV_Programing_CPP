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
    
    // [1]从摄像头读入视频
    // VideoCapture capture(0);
    VideoCapture capture;
    capture.open(0);
    
    Mat srcFrame, dstFrame, edge, grayFrame; // 参数定义
    capture >> srcFrame;
    dstFrame.create(srcFrame.size(), srcFrame.type());
    
    // [2]循环显示每一帧
    while (1) {
        
        capture >> srcFrame;  // 读取当前帧
        imshow("读取视频", srcFrame); // 显示当前帧
        cvtColor(srcFrame, grayFrame, COLOR_BGR2GRAY);
        blur(grayFrame, edge, Size(3, 3));
        Canny(edge, edge, 3, 9, 3);
        imshow("Canny边缘检测效果图", edge);
        waitKey(30); // 延时30ms

    }

    return 0;
}
