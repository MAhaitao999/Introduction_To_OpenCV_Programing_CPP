#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 1. 点的表示: Point类
    // Point point;
    // point.x = 10;
    // point.y = 20;
    Point point = Point(10, 8);
    cout << point << endl;
    
    // 2. 颜色的表示: Scalar类
    Scalar scalar(10, 10, 1);
    cout << Scalar(10, 10, 10) << endl;
    
    // 3. 尺寸的表示: Size类
    cout << Size(5, 5) << endl;
    
    // 4. 矩形的表示: Rect类
    Rect rect1(256, 256, 128, 128); 
    Rect rect2(224, 224, 128, 128);
    Rect rect_and = rect1 & rect2;
    Rect rect_or = rect1 | rect2;
    cout << rect1 << endl;
    cout << rect2 << endl;
    cout << rect_and << endl;
    cout << rect_or << endl;
    
    // 5. 颜色空间转换: cvtColor()函数
    Mat srcImage = imread("cat.jpg", 1);
    Mat dstImage;
    cvtColor(srcImage, dstImage, COLOR_BGR2Lab);
    imshow("效果图", dstImage);
    waitKey();

    return 0;
    
}
