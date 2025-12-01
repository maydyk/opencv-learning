#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat img1;

void tb1_Callback(int value, void *)
{
    Mat temp = img1 + value;
    imshow("main_win", temp);
}

int main()
{
    img1 = imread("lena.jpg", IMREAD_GRAYSCALE);
    if (img1.empty())
    {
        cout << "Cannot load image!" << endl;
        return -1;
    }

    int tb1_value = 0;

    // load trackbar value
    FileStorage fs1("config.xml", FileStorage::READ);
    tb1_value=fs1["tb1_value"];     // method 1
    fs1["tb1_value"] >> tb1_value; // method 2
    fs1.release();

    // create trackbar
    namedWindow("main_win");
    createTrackbar("brightness", "main_win", &tb1_value,
                   255, tb1_Callback);
    tb1_Callback(tb1_value, NULL);

    waitKey();

    // save trackbar value upon exiting
    FileStorage fs2("config.xml", FileStorage::WRITE);
    fs2 << "tb1_value" << tb1_value;
    fs2.release();

    return 0;
}

