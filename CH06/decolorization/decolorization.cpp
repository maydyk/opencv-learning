#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(const int argc, const char* argv[]) {
    // Load and show images
    cv::Mat source = cv::imread("color_image_3.png", cv::IMREAD_COLOR);
    cv::imshow("source", source);

    // Firstly compute and show standard grayscale conversion
    cv::Mat grayscale = cv::Mat(source.size(), CV_8UC1);
    cv::cvtColor(source, grayscale, cv::COLOR_BGR2GRAY);
    cv::imshow("grayscale", grayscale);

    // Now compute and show decolorization
    cv::Mat decolorized = cv::Mat(source.size(), CV_8UC1);
    cv::Mat dummy = cv::Mat(source.size(), CV_8UC3);
    cv::decolor(source, decolorized, dummy);
    cv::imshow("decolorized", decolorized);

    std::cout << "\nDone! Press any key to exit..." << std::endl;
    cv::waitKey(0);
    return 0;
}
