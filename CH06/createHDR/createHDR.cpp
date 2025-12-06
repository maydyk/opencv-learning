#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <format>
#include <array>
#include <string>
#include <ranges>

int main(const int argc, const char* argv[]) {
    std::vector<cv::Mat> images;
    std::vector<float> times;

    // Load images and exposures
    try {
        std::array<std::pair<std::string, float>, 3> files = {
            std::make_pair("1div66.jpg", 1.f/66),
            std::make_pair("1div32.jpg", 1.f/32),
            std::make_pair("1div12.jpg", 1.f/12),
        };

        std::ranges::for_each(files, [&images, &times](auto p) {
            auto [file, time] = p;
            cv::Mat img = cv::imread(file);
            if (img.empty()) {
                throw std::runtime_error(std::format("Cannot read the input image {}.", file));
            }

            images.emplace_back(std::move(img));
            times.emplace_back(time);
        });
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    // Estimate camera response
    cv::Mat response;
    cv::Ptr<cv::CalibrateDebevec> calibrate = cv::createCalibrateDebevec();
    calibrate->process(images, response, times);

    // Show the estimated camera response function
    std::cout << response << std::endl;

    // Create and write the HDR image
    cv::Mat hdr;
    cv::Ptr<cv::MergeDebevec> merge_devebec = cv::createMergeDebevec();
    merge_devebec->process(images, hdr, times, response);
    if (!cv::imwrite("hdr.jpg", hdr)) {
        std::cout << "Cannot write the result image.";
        return -1; 
    }

    std::cout << "Done! Press any key to exit" << std::endl;
    cv::waitKey(0);

    return 0;
}