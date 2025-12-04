#include <opencv2/opencv.hpp>
#include <ranges>
#include <utils.h>

int main(const int argc, const char* argv[]) {
    cv::Mat image = cv::imread("Lovebird.jpg");
    cv::imshow("Picture", image);

    // Convert to CIE XYZ
    cv::cvtColor(image, image, cv::COLOR_BGR2XYZ);

    // Split to channels
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Show channels in gray scale
    cv::namedWindow("X channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("X channel (gray)", channels[0]);
    cv::namedWindow("Y channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Y channel (gray)", channels[1]);
    cv::namedWindow("Z channel (gray)", cv::WINDOW_AUTOSIZE);
    cv::imshow("Z channel (gray)", channels[2]);

    // Show channels in BGR
    std::vector<cv::Mat> separatedChannels = showSeparatedChannels(channels);
    std::ranges::for_each(separatedChannels, [](cv::Mat& channel) {
        cv::cvtColor(channel, channel, cv::COLOR_XYZ2BGR);
    });

    cv::namedWindow("X channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("X channel", separatedChannels[0]);
    cv::namedWindow("Y channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("Y channel", separatedChannels[1]);
    cv::namedWindow("Z channel", cv::WINDOW_AUTOSIZE);
    cv::imshow("Z channel", separatedChannels[2]);

    cv::waitKey(0);
    return 0;
}