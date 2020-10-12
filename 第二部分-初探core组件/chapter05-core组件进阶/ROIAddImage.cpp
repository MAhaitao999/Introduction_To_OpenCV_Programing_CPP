#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// 利用感兴趣区域ROI实现图像叠加

bool ROI_AddImage() {
    // [1] 读入图像
    Mat srcImage1 = imread("cat.jpg");
    Mat logoImage = imread("baboon2.jpg");
    if (!srcImage1.data) {
        printf("读取srcImage1错误~! \n");
        return false;
    }
    if (!logoImage.data) {
        printf("读取logoImage错误~! \n");
        return false;
    }
    
    // [2]定义一个Mat类型并给其设定ROI区域
    Mat imageROI = srcImage1(Rect(200, 500, logoImage.cols, logoImage.rows));
    
    // [3]加载掩模(必须是灰度图)
    Mat mask = imread("baboon2.jpg", 0);
    
    // [4]将掩模复制到ROI
    logoImage.copyTo(imageROI, mask);
    
    // [5]显示结果
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
    
    return true;
}


int main(int argc, char** argv) {
    
    bool result = ROI_AddImage();
    
    waitKey(0);
    
    return 0;
    
}
