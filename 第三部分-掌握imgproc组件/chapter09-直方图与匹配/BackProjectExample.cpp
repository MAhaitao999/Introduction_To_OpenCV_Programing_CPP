#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "[原始图]"

Mat g_srcImage;
Mat g_hsvImage;
Mat g_hueImage;
int g_bins = 30; // 直方图组距

void on_BinChange(int, void*);

int main(int argc, char *argv[]) {

    // [1]读取源图像, 并转换到HSV空间
    g_srcImage = imread("hand1.jpg", 1);
    if (!g_srcImage.data) {
        printf("读取图片错误, 请确定目录下是否有指定图片存在~! \n");
        return false;
    }
    
    cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
    
    // [2]分离Hue色调通道
    g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
    int ch[] = {0, 0};
    mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);
    
    // [3]创建Trackbar来输入bin的数量
    namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
    createTrackbar("色调组距", WINDOW_NAME1, &g_bins, 180, on_BinChange);
    on_BinChange(0, 0); // 进行一次初始化
    
    // [4]显示效果图
    imshow(WINDOW_NAME1, g_srcImage);
    
    // 等待用户按键
    waitKey(0);

    return 0;

}

void on_BinChange(int, void*) {
    // 参数准备
    MatND hist;
    int histSize = MAX(g_bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges = {hue_range};
    
    // 计算直方图并归一化
    calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    
    // 计算反向投影
    MatND backproj;
    calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);
    
    // 显示反向投影
    imshow("反向投影图", backproj);
    
    // 绘制直方图的参数准备
    int w = 400;
    int h = 400;
    int bin_w = cvRound((double)w/histSize);
    Mat histImg = Mat::zeros(w, h, CV_8UC3);
    
    // 绘制直方图
    for (int i=0; i < g_bins; i++) {
        rectangle(histImg, Point(i*bin_w, h), Point((i+1)*bin_w, h-cvRound(hist.at<float>(i)*h/255.0)), Scalar(100, 123, 255), -1);
    }
    
    // 显示直方图
    imshow("直方图", histImg);
    
}
