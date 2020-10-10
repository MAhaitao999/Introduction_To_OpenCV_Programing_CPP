#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    
    int divideWith = 40;
    uchar table[256];
    
    for (int i=0; i < 256; ++i) {
        table[i] = divideWith * (i/divideWith);
    }
    
    // 首先我们建立一个Mat型用于查找表
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for (int i=0; i < 256; ++i) {
        p[i] = table[i];
    }
    
    Mat I = imread("cat.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat J;
    
    // 然后我们调用函数(I是输入, J是输出)
    for (int i=0; i < 10; ++i) {
        LUT(I, lookUpTable, J);
    }
    
    imshow("映射之前的图像", I);
    imshow("映射之后的图像", J);
    waitKey(0);

    return 0;
    
}
