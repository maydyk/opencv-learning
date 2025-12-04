#include <opencv2/opencv.hpp>
#include <ranges>
#include <numeric>
#include "utils.h"


std::vector<cv::Mat> showSeparatedChannels(const std::vector<cv::Mat>& channels) {
    const auto channel_count = channels.size();
    const auto separated_channels =
        channels | std::views::enumerate |
        std::views::transform([channel_count](auto p) {
            auto [index, channel] = p;

            // Append zero channels to each color channel.
            cv::Mat zero = cv::Mat::zeros(channel.rows, channel.cols, channel.type());

            const auto aux_view = std::views::iota(decltype(channel_count)(0), channel_count) |
                std::views::transform([index, &zero, &channel](auto aux_index) {
                    if (aux_index == index) {
                        return channel;
                    } else {
                        return zero;
                    }
                });
            
            cv::Mat display;
            cv::merge(std::vector<cv::Mat>(aux_view.cbegin(), aux_view.cend()), display);
            return display;
        });

    return std::vector<cv::Mat>(separated_channels.cbegin(), separated_channels.cend());
}
