#include <opencv2/opencv.hpp>

int main(const int argc, const char* argv[]) {
    // Show bayered image in color
    cv::Mat bayer_color = cv::imread("Lovebird_bayer_color.jpg");
    cv::namedWindow("Bayer picture in color", cv::WINDOW_AUTOSIZE);
    cv::imshow("Bayer picture in color", bayer_color);

    // Load bayered image
    cv::Mat bayer = cv::imread("Lovebird_bayer.jpg", CV_8UC3);
    cv::namedWindow("Bayer picture ", cv::WINDOW_AUTOSIZE);
    cv::imshow("Bayer picture ", bayer);

    cv::Mat imageColor;
    cv::cvtColor(bayer, imageColor, cv::COLOR_BayerRG2BGR);

    cv::namedWindow("Color picture", cv::WINDOW_AUTOSIZE);
    cv::imshow("Color picture", imageColor);

    cv::waitKey(0);
    return 0;
}
