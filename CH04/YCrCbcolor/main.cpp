#include <opencv2/opencv.hpp>
#include <array>
#include <ranges>
#include <utils.h>

int main(const int argc, const char* argv[]) {
    // Load the image
    cv::Mat image = cv::imread("Lovebird.jpg");
    cv::imshow("Picture", image);

    // Transform to YCrCb
    cv::cvtColor(image, image, cv::COLOR_BGR2YCrCb);

    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Show channels in gray scale
    const std::array channelNamesGray = {
        "Y channel (gray)",
        "Cr channel (gray)",
        "Cb channel (gray)",
    };

    std::ranges::for_each(enumerate(channelNamesGray), [&channels](auto p) {
        auto [index, channelName] = p;
        cv::namedWindow(channelName, cv::WINDOW_AUTOSIZE);
        cv::imshow(channelName, channels[index]);
    });

    // Show channels in BGR
    std::vector<cv::Mat> separatedChannels = showSeparatedChannels(channels);
    std::ranges::for_each(separatedChannels, [] (cv::Mat& channel) {
        cv::cvtColor(channel, channel, cv::COLOR_YCrCb2BGR);
    });

    const std::array channelNames = {
        "Y channel",
        "Cr channel",
        "Cb channel",
    };

    std::ranges::for_each(enumerate(channelNames), [&separatedChannels](auto p) {
        auto [index, channelName] = p;
        cv::namedWindow(channelName, cv::WINDOW_AUTOSIZE);
        cv::imshow(channelName, separatedChannels[index]);
    });

    cv::waitKey(0);
    return 0;
}