#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // [0]变量定义
    Mat srcImage, dstImage;
    Mat map_x, map_y;
    
    // [1]载入原始图
    srcImage = imread("cat.jpg", 1);
    if (!srcImage.data) {
        printf("读取图片错误, 请确定目录下是否有imread函数指定的图片存在~! \n");
        return -1;
    }
    
    imshow("原始图", srcImage);
    
    // [2]创建和原始图一样的效果图, x重映射图, y重映射图
    dstImage.create(srcImage.size(), srcImage.type());
    map_x.create(srcImage.size(), CV_32FC1);
    map_y.create(srcImage.size(), CV_32FC1);
    
    // [3]双层循环, 遍历每一个像素点, 改变map_x & map_y的值
    for (int i=0; i < srcImage.rows; i++) {
        for (int j=0; j < srcImage.cols; j++) {
            // 改变map_x & map_y的值
            map_x.at<float>(i, j) = static_cast<float>(srcImage.cols - j);
            map_y.at<float>(i, j) = static_cast<float>(srcImage.rows - i);
        }
    }
    
    /*
    for (int j=0; j < srcImage.rows; j++) {
        for (int i=0; i < 1; i++) {
            cout << "(" << map_x.at<float>(j, i) << ", " << map_y.at<float>(j, i) << ")" << endl;    
        }
    }
     * */
    
    // [4] 进行重映射操作
    remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
    
    // [5] 显示效果图
    imshow("[程序窗口]", dstImage);
    
    waitKey();
    
    return 0;
    
}
