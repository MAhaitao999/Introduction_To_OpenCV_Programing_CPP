#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    
    Mat image = imread("cat.jpg");
    if (!image.data) {
        cout << "read image error" << endl;
        return -1;
    }
    imshow("Original", image);
    
    vector<Mat> channels;
    split(image, channels);
    
#if 0
    cout << "使用第一种方法" << endl;
    imshow("B", channels.at(0));
    imshow("G", channels.at(1));
    imshow("R", channels.at(2));
#else
    cout << "使用第二种方法" << endl;
    imshow("B", channels[0]);
    imshow("G", channels[1]);
    imshow("R", channels[2]);
#endif
    waitKey(0);
    
    return 0;
    
}
