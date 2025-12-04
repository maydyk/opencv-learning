#include <opencv2/opencv.hpp>

#include <array>
#include <utils.h>

int main(const int argc, const char* argv[]) {
    // Load the image
    cv::Mat image = cv::imread("Lovebird.jpg");
    cv::imshow("Picture", image);

    // Transform to HSV
    cv::cvtColor(image, image, cv::COLOR_BGR2Lab);

    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Show channels in gray scale
    const std::array channelNames = {
        "L channel (gray)",
        "a channel (gray)",
        "b channel (gray)",
    };

    std::ranges::for_each(enumerate(channelNames), [&channels](const auto p) {
        const auto [index, channelName] = p;
        cv::namedWindow(channelName, cv::WINDOW_AUTOSIZE);
        cv::imshow(channelName, channels[index]);
    });

    cv::namedWindow("CIE Lab image (all channels)", cv::WINDOW_AUTOSIZE);
    cv::imshow("CIE Lab image (all channels)", image);

    cv::waitKey(0);
    return 0;
}