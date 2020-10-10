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
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 载入图片
    Mat image = imread("cat.jpg", 199); // 199表示缩小1/8, 三通道
    Mat logo = imread("mug.jpg");
    
    // 载入后先显示
    namedWindow("[2]原画图");
    imshow("[2]原画图", image);
    
    namedWindow("[3]logo图");
    imshow("[3]logo图", logo);
    
    // 定义一个Mat类型, 用于存放, 图像的ROI
    Mat imageROI;
    // 方法一
    imageROI = image(Rect(0, 0, logo.cols, logo.rows));
    // 方法二
    // imageROI = image(Range(350, 350+logo.rows), Range(800, 800+logo.cols));
    
    // 将logo加到原图上
    addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);
    
    // 显示结果
    namedWindow("[4]原画+logo图");
    imshow("[4]原画+logo图", image);
    
    imwrite("由imwrite生成的图片.jpg", image);
    
    waitKey(0);

    return 0;
}
