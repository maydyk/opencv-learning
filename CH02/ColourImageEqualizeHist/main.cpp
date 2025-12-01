#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>

cv::Mat histogram_calculation(const cv::Mat& Image) {
    const int histSize = 255;

    // Setup ranges for [B, G, R]
    const float range [] = {0, 256 };
    const float *histRange = { range };

    const bool uniform = true; const bool accumulate = false;

    cv::Mat b_hist, g_hist, r_hist;

    std::vector<cv::Mat> bgr_planes;
    cv::split(Image, bgr_planes);

    cv::calcHist(&bgr_planes[0], 1, nullptr, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[1], 1, nullptr, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgr_planes[2], 1, nullptr, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Draw histograms for channels B, G, R
    const int hist_w = 512; const int hist_h = 400;
    const int bin_w = cvRound((double) hist_w / histSize);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    // Normalize the result to the range [0, histImage.rows]
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    // Draw for each channel
    for (int i = 1; i < histSize; ++i) {
        cv::line(
            histImage,
            cv::Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
            cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))    ),
            cv::Scalar(255, 0, 0), 2, cv::LINE_4, 0
        );

        cv::line(
            histImage,
            cv::Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
            cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))    ),
            cv::Scalar(0, 255, 0), 2, cv::LINE_4, 0
        );
        
        cv::line(
            histImage,
            cv::Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
            cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))    ),
            cv::Scalar(0, 0, 255), 2, cv::LINE_4, 0)
            ;
    }

    return std::move(histImage);
}

int main(int, char* []) {
    cv::Mat src, imageEq;
    cv::Mat histImage;

    // Read the source image
    src = cv::imread("fruits.jpg");
    if ( ! src.data ) {
        printf("Cannot load the image!\n");
        exit(1);
    }

    // Separate the image to 3 channels (B, G, R)
    std::vector<cv::Mat> bgr_planes;
    split(src, bgr_planes);

    // Display results
    cv::imshow("Source image", src);

    // Calculate the histogram to each channel of the source image
    histImage = histogram_calculation(src);

    // Display the histogram for each colour channel
    cv::imshow("Colour Image Histogram", histImage);

    // Equalized image

    // Apply histogram equalization to each channel
    cv::equalizeHist(bgr_planes[0], bgr_planes[0]);
    cv::equalizeHist(bgr_planes[1], bgr_planes[1]);
    cv::equalizeHist(bgr_planes[2], bgr_planes[2]);

    // Merge the equalized image channels into the equalized image
    cv::merge(bgr_planes, imageEq);

    // Display the equalized image
    cv::imshow("Equalized Image", imageEq);
    
    // Calculate the histogram to each channel of the equalized image
    histImage = histogram_calculation(imageEq);

    // Display the histogram of the equalized image
    cv::imshow("Equalized Colour Image Histogram", histImage);

    // Wait until the user exits the program
    cv::waitKey();

    return 0;
}
