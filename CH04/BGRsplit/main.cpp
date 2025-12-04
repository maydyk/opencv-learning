#include <opencv2/opencv.hpp>
#include <ranges>
#include <numeric>

#include <utils.h>

int main(int argc, const char* argv[]) {
    // Load the image
    cv::Mat image = cv::imread("BGR.png");
    cv::imshow("Picture", image);

    // The next part splits the picture into each channel and show it
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Show channels in gray mode
    cv::namedWindow("Blue channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Blue channel (gray)", channels[0]);
    cv::namedWindow("Green channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Green channel (gray)", channels[1]);
    cv::namedWindow("Red channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Red channel (gray)", channels[2]);

    // Show channels as BGR
    std::vector<cv::Mat> separatedChannels { showSeparatedChannels(channels) };
    cv::namedWindow("Blue channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("Blue channel", separatedChannels[0]);
    cv::namedWindow("Green channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("Green channel", separatedChannels[1]);
    cv::namedWindow("Red channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("Red channel", separatedChannels[2]);

    cv::waitKey(0);
    return 0;
}
