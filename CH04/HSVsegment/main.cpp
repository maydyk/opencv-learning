#include <opencv2/opencv.hpp>

int main(const int argc, const char* argv[]) {

    // Load the image
    cv::Mat image = cv::imread("hand.jpg");
    cv::namedWindow("Picture", cv::WINDOW_AUTOSIZE);
    cv::imshow("Picture", image);

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Select pixels
    cv::Mat bw;
    cv::inRange(hsv, cv::Scalar(0, 10, 60), cv::Scalar(20, 150, 255), bw);

    cv::namedWindow("Selected pixels", cv::WINDOW_AUTOSIZE);
    cv::imshow("Selected pixels", bw);

    cv::waitKey(0);
    return 0;
}