#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));
    
    // 风格一: OpenCV默认风格
    cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
    
    // 风格二: Python风格
    cout << "r (Python风格) = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    
    // 风格三: CSV风格
    cout << "r (CSV风格) = " << format(r, Formatter::FMT_CSV) << ";" << endl << endl;
    
    // 风格四: Numpy风格
    cout << "r (Numpy风格) = " << format(r, Formatter::FMT_NUMPY) << ";" << endl << endl;
    
    // 风格五: C语言风格
    cout << "r (Ｃ语言风格) = " << format(r, Formatter::FMT_C) << ";" << endl << endl;
    
    // 风格六: Matlab风格
    cout << "r (Matlab风格) = " << format(r, Formatter::FMT_MATLAB) << ";" << endl << endl;


    return 0;
}
