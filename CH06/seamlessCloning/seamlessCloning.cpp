#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main (const int argc, const char* argv[]) {
    // Load and show images
    cv::Mat source = cv::imread("source1.png", cv::IMREAD_COLOR);
    cv::Mat destination = cv::imread("destination1.png", cv::IMREAD_COLOR);
    cv::Mat mask = cv::imread("mask.png", cv::IMREAD_COLOR);
    cv::imshow("source", source);
    cv::imshow("destination", destination);
    cv::imshow("mask", mask);

    cv::Mat result;
    cv::Point p;    // p will near top right corner
    p.x = (float) 2*destination.size().width/3;
    p.y = (float) destination.size().height/4;
    cv::seamlessClone(source, destination, mask, p, result, cv::NORMAL_CLONE);
    cv::imshow("result", result);

    std::cout << "\nDone! Press any key to exit...\n";
    cv::waitKey(0);
    return 0;
}