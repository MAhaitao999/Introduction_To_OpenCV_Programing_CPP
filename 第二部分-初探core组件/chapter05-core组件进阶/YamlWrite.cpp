#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 初始化
    FileStorage fs("test.yaml", FileStorage::WRITE);
    
    // 开始文件写入
    fs << "frameCount" << 5;
    time_t rawtime; time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 1000, 240, 0, 0, 1);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs << "features" << "[";
    for (int i=0; i < 3; i++) {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;
        
        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
        for (int j=0; j < 8; j++) {
            fs << ((lbp >> j) & 1);
        }
        fs << "]" << "}";
    }
    fs << "]";
    
    fs.release();
    
    printf("文件读写完毕, 请在工程目录下查看生成的文件~");
    getchar();
    
    return 0;
    
}
