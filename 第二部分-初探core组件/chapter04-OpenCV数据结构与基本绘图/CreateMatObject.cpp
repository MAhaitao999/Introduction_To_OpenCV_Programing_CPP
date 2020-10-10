#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 方法一: 使用Mat()构造函数
    Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;
    
    // 方法二: 在C/C++中通过构造函数进行初始化
    int sz[3] = {2, 2, 2};
    Mat L(3, sz, CV_8UC1, Scalar::all(0));
    
    // 方法三: 为已存在的IplImage指针创建信息头
    IplImage* img = cvLoadImage("cat2.jpg", 1);
    Mat mtx = cv::cvarrToMat(img); // 转换IplImage* -> Mat
    
    // 方法四: 利用Create()函数
    M.create(4, 4, CV_8UC(2));
    cout << "M = " << endl << " " << M << endl << endl;
    
    // 方法五: 采用Matlab式的初始化方式
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;
    
    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;
    
    Mat Z = Mat::zeros(3, 3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;
    
    // 方法六: 对小矩阵使用逗号分割式初始化函数
    Mat C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;
    
    // 方法七: 为已存在的对象创建新信息头
    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;

    return 0;
}
