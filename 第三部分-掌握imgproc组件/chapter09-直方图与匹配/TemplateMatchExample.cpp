#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "[原始图片]"
#define WINDOW_NAME2 "[效果窗口]"

Mat g_srcImage;
Mat g_templateImage;
Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void*);

int main(int argc, char *argv[]) {

    // [1] 载入原图和模板块
    g_srcImage = imread("beauty.jpg", 1);
    g_templateImage = imread("beauty_face.jpg", 1);
    
    // [2] 创建窗口
    namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
    namedWindow(WINDOW_NAME2, CV_WINDOW_AUTOSIZE);
    
    // [3] 创建滚动条并进行一次初始化
    createTrackbar("方法", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
    on_Matching(0, 0);
    
    waitKey(0);
    
    return 0;
    
}

void on_Matching(int, void*) {
    // [1] 给局部变量初始化
    Mat srcImage;
    g_srcImage.copyTo(srcImage);
    
    // [2] 初始化用于结果输出的矩阵
    int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
    int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
    g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);
    
    // [3] 进行匹配和标准化
    matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
    normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
    
    // [4] 通过函数minMaxLoc定位最匹配的位置
    double minValue;
    double maxValue;
    Point minLocation;
    Point MaxLocation;
    Point matchLocation;
    minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &MaxLocation, Mat());
    
    // [5] 对于方法SQDIFF和SQDIFF_NORMED, 越小的数值有着更高的匹配结果, 而其余的方法, 数值越大匹配效果越好
    if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED) {
        matchLocation = minLocation;
    }
    else {
        matchLocation = MaxLocation;
    }
    
    // [6] 绘制出矩形, 并显示最终结果
    rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
            Scalar(0, 0, 255), 2, 8, 0);
    rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
            Scalar(0, 0, 255), 2, 8, 0);
    imshow(WINDOW_NAME1, srcImage);
    imshow(WINDOW_NAME2, g_resultImage);
    
}
