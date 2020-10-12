#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    
    Mat image = imread("baboon2.jpg");
    if (!image.data) {
        cout << "read image error" << endl;
        return -1;
    }
    imshow("Original", image);
    
    vector<Mat> channels;
    split(image, channels);
    
#if 0
    imshow("B", channels.at(0));
    imshow("G", channels.at(1));
    imshow("R", channles.at(2));
#else
    imshow("B", channels[0]);
    imshow("G", channels[1]);
    imshow("R", channels[2]);
#endif
    
    Mat mergedst;
#if 0
    Mat mergesrc[3] = {channels[0], channels[1], channels[2]};
    merge(mergesrc, 3, mergedst);
#else
    vector<Mat> mergesrc;
    mergesrc.push_back(channels[0]);
    mergesrc.push_back(channels[1]);
    mergesrc.push_back(channels[2]);
    merge(mergesrc, mergedst);
#endif
    
    imshow("Merged", mergedst);
    waitKey(0);
    
    return 0;
    
}
