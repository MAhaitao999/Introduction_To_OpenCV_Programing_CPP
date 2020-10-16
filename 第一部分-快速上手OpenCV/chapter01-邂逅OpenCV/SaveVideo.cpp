#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <regex>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    
    // Read in the video
    cv::VideoCapture cap;
    cap.open("/home/transwarp/Downloads/test1.avi");
    Size size = Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
    cout << size << endl;
    VideoWriter writer;
    writer.open("binary_test001.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, size, true);
    
    if (!cap.isOpened()) {
        cout << "视频打开失败" << endl;
        return -1;
    }

    Mat frame, gray;
    while (cap.read(frame)) {
        // 转化为黑白图像
        cvtColor(frame, gray, COLOR_BGR2GRAY);
            
        // 二值化处理
        threshold(gray, gray, 0, 255, THRESH_BINARY | THRESH_OTSU);
        cvtColor(gray, gray, COLOR_GRAY2BGR);
        imshow("二值图", gray);
        writer.write(gray);
        waitKey(40);
    }

    cap.release();
   
    return 0;
    
}
