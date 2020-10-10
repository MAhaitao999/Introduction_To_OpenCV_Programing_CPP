/*************************************************************************
    > File Name: HelloOpenCV.cpp
    > Author: Henry Ma
    > Mail: iloveicRazavi@gmail.com 
    > Created Time: 2020年07月31日 星期五 16时26分44秒
 ************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    
    // [1]读入一张图片
    Mat img = imread("cat.jpg");

    // [2]在窗口中显示载入的图片
    imshow("载入的图片", img);

    // [3]等待6000ms后窗口自动关闭
    waitKey(6000);

    return 0;
}
