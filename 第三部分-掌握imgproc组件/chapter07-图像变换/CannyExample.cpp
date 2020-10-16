#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <regex>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 载入原图
    Mat src = imread("cat.jpg");
    Mat src1 = src.clone();
    
    // 显示原始图
    imshow("[原始图]Canny边缘检测", src);
    
    // 高阶的Canny用法, 转成灰度图, 降噪, 用canny, 最后将得到的边缘作为
    // 掩码, 拷贝原图到效果图上, 得到彩色的边缘图
    Mat dst, edge, gray;
    
    // [1] 创建与src同类型和大小的矩阵(dst)
    dst.create(src1.size(), src1.type());
    
    // [2] 将原图像转化为灰度图像
    cvtColor(src1, gray, COLOR_BGR2GRAY);
    
    // [3] 先使用3x3内核来降噪
    blur(gray, edge, Size(3, 3));
    
    // [4] 运行Canny算子
    Canny(edge, edge, 3, 9, 3);
    // cout << format(edge, Formatter::FMT_NUMPY) << endl;
    
    // [5] 将dst内的所有元素设置为0
    dst = Scalar::all(0);
    
    // [6] 使用Canny算子输出的边缘图作为掩码, 来将原图拷贝到目标图中
    src1.copyTo(dst, edge);
    
    // [7] 显示效果图 
    imshow("[效果图]Canny边缘检测", dst);
    
    waitKey(0);
   
    return 0;
    
}
