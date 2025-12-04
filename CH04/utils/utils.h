#pragma once
#include <opencv2/opencv.hpp>
#include <ranges>

std::vector<cv::Mat> showSeparatedChannels(const std::vector<cv::Mat>& channels);

// See https://medium.com/@batteriesnotincludeddev/indexed-for-each-in-modern-c-7df21fce72a1 for details
auto enumerate(const auto& data) {
    return data | std::views::transform([i = 0](const auto& value) mutable {
        return std::make_pair(i++, value);
    });
}
