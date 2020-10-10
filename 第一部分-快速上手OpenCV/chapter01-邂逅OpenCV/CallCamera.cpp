/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: transwarp
 *
 * Created on October 9, 2020, 5:51 PM
 */

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
    
    
    // [2]循环显示每一帧
    while (1) {
        Mat frame; // 定义一个Mat变量, 用于存储每一帧的图像
        capture >> frame;  // 读取当前帧
        imshow("读取视频", frame); // 显示当前帧
        waitKey(30); // 延时30ms

    }

    return 0;
}


