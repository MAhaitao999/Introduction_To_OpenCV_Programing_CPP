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

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);


int main(int argc, char** argv) {
    
    // [1] 创建原始图片并显示
    Mat srcImage = imread("cat.jpg");
    imshow("原始图像", srcImage);
    
    // [2] 按照原始图的参数规格来创建效果图
    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
    
    // [3] 记录起始时间
    double time0 = static_cast<double>(getTickCount());
    
    // [4] 调用颜色空间缩减函数
    colorReduce3(srcImage, dstImage, 32);
    
    // [5] 计算运行时间并输出
    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout << "此方法运行时间为: " << time0 << "秒" << endl;
    
    // [6] 显示效果图
    imshow("效果图", dstImage);
    
    waitKey(0);
    
    return 0;
    
}

// 使用[指针访问: C操作符[]]方法版的颜色空间缩减函数
void colorReduce1(Mat& inputImage, Mat& outputImage, int div) {
    // 参数准备
    outputImage = inputImage.clone(); // 复制实参到零时变量
    int rowNumber = outputImage.rows; // 行数
    int colNumber = outputImage.cols * outputImage.channels();
    
    // 双重循环, 遍历所有的像素值
    for (int i=0; i < rowNumber; i++) {
        uchar* data = outputImage.ptr<uchar>(i); // 获取第i行的首地址
        for (int j=0; j < colNumber; j++) { // 列循环
            data[j] = data[j]/div*div + div/2;
        }
    }
}

// 使用[迭代器]方法版本的颜色空间缩减函数
void colorReduce2(Mat& inputImage, Mat& outputImage, int div) {
    // 参数准备
    outputImage = inputImage.clone();
    // 获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  // 初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); // 终止位置的迭代器
    
    // 存取彩色图像像素
    for (; it != itend; ++it) {
        // 开始处理每个像素
        (*it)[0] = (*it)[0]/div*div+div/2;
        (*it)[1] = (*it)[1]/div*div+div/2;
        (*it)[2] = (*it)[2]/div*div+div/2;
    }
}

// 使用[动态地址运算配合at]方法版本的颜色空间缩减函数
void colorReduce3(Mat& inputImage, Mat& outputImage, int div) {
    // 参数准备
    outputImage = inputImage.clone(); // 复制实参到临时变量
    int rowNumber = outputImage.rows; // 行数
    int colNumber = outputImage.cols; // 列数
    
    // 存取彩色图像像素
    for (int i=0; i < rowNumber; i++) {
        for (int j=0; j < colNumber; j++) {
            // 开始处理每个像素
            outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0]/div*div+div/2; // 蓝色通道
            outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1]/div*div+div/2; // 绿色通道
            outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2]/div*div+div/2; // 红色通道
        }
    }
}

