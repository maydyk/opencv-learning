#include <opencv2/opencv.hpp>

int main(const int argc, const char* argv[]) {

    // Load the image
    cv::Mat image = cv::imread("hand.jpg");
    cv::namedWindow("Picture", cv::WINDOW_AUTOSIZE);
    cv::imshow("Picture", image);

    cv::Mat ycrcb;
    cv::cvtColor(image, ycrcb, cv::COLOR_BGR2YCrCb);

    // Select pixels
    cv::Mat bw;
    cv::inRange(ycrcb, cv::Scalar(0, 133, 77), cv::Scalar(255, 173, 177), bw);

    cv::namedWindow("Selected pixels", cv::WINDOW_AUTOSIZE);
    cv::imshow("Selected pixels", bw);

    cv::waitKey(0);
    return 0;
}