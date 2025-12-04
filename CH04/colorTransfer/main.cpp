#include <opencv2/opencv.hpp>

int main(const int argc, const char* argv[]) {
    // Load the images
    cv::Mat src = cv::imread("clock_tower.jpg");
    cv::Mat tar = cv::imread("big_ben.jpg");

    // Convert to Lab space and CV_32F1
    cv::Mat src_lab, tar_lab;
    cv::cvtColor(src, src_lab, cv::COLOR_BGR2Lab);
    cv::cvtColor(tar, tar_lab, cv::COLOR_BGR2Lab);

    src_lab.convertTo(src_lab, CV_32FC1);
    tar_lab.convertTo(tar_lab, CV_32FC1);

    // Find mead and std of each channel for each image.
    cv::Mat mean_src, mean_tar, stdd_src, stdd_tar;
    cv::meanStdDev(src_lab, mean_src, stdd_src);
    cv::meanStdDev(tar_lab, mean_tar, stdd_tar);

    // Split into individual channels
    std::vector<cv::Mat> src_chan, tar_chan;
    cv::split(src_lab, src_chan);
    cv::split(tar_lab, tar_chan);

    // For each channel calculate color distribution
    for (int i = 0; i < 3; ++i) {
        tar_chan[i] -= mean_tar.at<double>(i);
        tar_chan[i] *= (stdd_src.at<double>(i) / stdd_src.at<double>(i));
        tar_chan[i] += mean_src.at<double>(i);
    }

    // Merge channels, convert to CV_U8C1 each channel and convert to BGR
    cv::Mat output;
    cv::merge(tar_chan, output);
    output.convertTo(output, CV_8UC1);
    cv::cvtColor(output, output, cv::COLOR_Lab2BGR);

    // show pictures
    cv::namedWindow("Source image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Source image", src);
    cv::namedWindow("Target image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Target image", tar);
    cv::namedWindow("Result image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Result image", output);

    cv::waitKey(0);
    return 0;
}