#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <memory>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

    // [1]载入原图并显示
    Mat srcImage = imread("baboon2.jpg", 1);
    imshow("原图", srcImage);
    
    if (!srcImage.data) {
        printf("读取文件失败~!\n");
        return -1;
    }
    
    // [2]定义变量
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0, 256};
    const float* ranges[] = {range};
    MatND redHist, greenHist, blueHist;
    int channels_r[] = {0};
    int channels_g[] = {1};
    int channels_b[] = {2};
    
    // [3]计算图像的直方图(红色部分)
    calcHist(&srcImage, 1, channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);
    // [4]计算图像的直方图(绿色部分)
    calcHist(&srcImage, 1, channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);
    // [5]计算图像的直方图(蓝色部分)
    calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);
    
    // 绘制出三色直方图
    // 参数准备
    double maxValue_red, maxValue_green, maxValue_blue;
    minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
    minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
    minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
    int scale = 1;
    int histHeight = 256;
    Mat histImage = Mat::zeros(histHeight, bins*3, CV_8UC3);
    
    // 正式开始绘制
    for (int i=0; i < bins; i++) {
        // 参数准备
        float binValue_red = redHist.at<float>(i);
        float binValue_green = greenHist.at<float>(i);
        float binValue_blue = blueHist.at<float>(i);
        int intensity_red = cvRound(binValue_red*histHeight/maxValue_red); // 要绘制的高度
        int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);
        int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);
        
        // 绘制红色分量的直方图
        rectangle(histImage, Point(i*scale, histHeight-1), Point((i+1)*scale-1, histHeight-intensity_red), Scalar(255, 0, 0));
        
        // 绘制绿色分量的直方图
        rectangle(histImage, Point((i+bins)*scale, histHeight-1), Point((i+bins+1)*scale-1, histHeight-intensity_green), Scalar(0, 255, 0));
        
        // 绘制红色分量的直方图
        rectangle(histImage, Point((i+bins*2)*scale, histHeight-1), Point((i+bins*2+1)*scale-1, histHeight-intensity_blue), Scalar(0, 0, 255));
    }
    
    // 在窗口中显示出绘制好的直方图
    imshow("图像的RGB直方图", histImage);
    waitKey(0);
    
    return 0;
}
