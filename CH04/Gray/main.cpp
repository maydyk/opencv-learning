#include <opencv2/opencv.hpp>

int main(const int argc, const char* argv[]) {
    // Load the image
    cv::Mat image = cv::imread("Lovebird.jpg");
    cv::namedWindow("Picture", cv::WINDOW_AUTOSIZE);
    cv::imshow("Picture", image);

    cv::Mat imageGrey;
    cv::cvtColor(image, imageGrey, cv::COLOR_BGR2GRAY);

    cv::namedWindow("Gray picture", cv::WINDOW_AUTOSIZE);
    cv::imshow("Gray picture", imageGrey);

    cv::waitKey(0);
    return 0;
}