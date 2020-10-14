#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    
    Mat src = imread("cat.jpg");
    imshow("[原始图]", src);
    
    Rect ccomp;
    floodFill(src, Point(30, 30), Scalar(155, 255, 255), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
    imshow("[效果图]", src);
    waitKey(0);
    
    return 0;
    
}
