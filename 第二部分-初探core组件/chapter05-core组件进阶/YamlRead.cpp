#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    
    // 初始化
    FileStorage fs2("test.yaml", FileStorage::READ);
    
    // 第一种方法, 对FileNode操作
    int frameCount = (int)fs2["frameCount"];
    
    std::string date;
    // 第二种方法, 使用FileNode运算符>>
    fs2["calibrationDate"] >> date;
    
    Mat cameraMatrix2, distCoeffs2;
    fs2["cameraMatrix"] >> cameraMatrix2;
    fs2["distCoeffs"] >> distCoeffs2;
    
    cout << "frameCount: " << frameCount << endl
         << "calibration date: " << date << endl
         << "camera matrix: " << cameraMatrix2 << endl
         << "distortion coeffs: " << distCoeffs2 << endl;
    
    FileNode features = fs2["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;
    
    // 使用FileNodeIterator遍历序列
    for (; it != it_end; ++it, idx++) {
        cout << "feature #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // 我们也可以使用filenode >> std::vector操作符来很容易地读数值阵列
        (*it)["lbp"] >> lbpval;
        for (int i=0; i < (int)lbpval.size(); i++) {
            cout << " " << (int)lbpval[i];
        }
        cout << ")" << endl;                
    }
    fs2.release();
    
    printf("\n文件读取完毕, 请输入任意键结束程序~");
    getchar();
    
    return 0;
    
}
