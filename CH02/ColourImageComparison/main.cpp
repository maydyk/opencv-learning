#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <format>
#include <ranges>

cv::Mat histogram_2D_calculation(const cv::Mat& src) {
    cv::Mat hsv;

    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    // Quantize the hue to 30-255 levels
    // and the saturation to 32-255 levels.
    const int hbins = 255, sbins = 255;
    const int histSize[] = { hbins, sbins };
    // Hue varies from 0 to 179. See cvtColor().
    const float hranges[] = { 0, 180 };
    // Saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum colour)
    const float sranges [] = { 0, 256 };

    const float *ranges[] = {hranges, sranges };
    cv::Mat hist, hist2;
    
    // Compute the histogram from the 0-th and 1-set channels
    const int channels[] = {0, 1 };
    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);
    
    double maxVal  = 0;
    cv::minMaxLoc(hist, nullptr, &maxVal, 0, 0);

    int scale = 1;
    cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);

    for (int h = 0; h < hbins; ++h) {
        for (int s = 0; s < sbins; ++s) {
            const float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            cv::rectangle(
                histImg,
                cv::Point(h*scale, s*scale),
                cv::Point((h+1)*scale - 1, (s+1)*scale -1 ),
                cv::Scalar::all(intensity),
                cv::FILLED
            );
        }
    }

    return std::move(histImg);
}

cv::Mat histogram_RG_calculation(const cv::Mat& src) {
    // Using 50 bins for red and 60 for green
    const int r_bins = 50, g_bins = 60;
    const int histSize[] = { r_bins, g_bins };
    
    // Red varies from 0 to 255, green varies from 0 to 255.
    const float r_range[] = { 0, 255 };
    const float g_range[] = { 0, 255 };

    const float* ranges[] = { r_range, g_range };

    // Use 0-th and the 1-st channels
    const int channels[] = { 0, 1 };

    // Histograms
    cv::Mat hist_base;

    // Calculate the histograms for the HSV (?) images
    cv::calcHist(&src, 1, channels, cv::Mat(), hist_base, 2, histSize, ranges, true, false);
    cv::normalize(hist_base, hist_base, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    return std::move(hist_base);
}

int main(int argc, char* argv[]) {
    cv::Mat src, imageEq;
    cv::Mat histImg, histImgEq;
    cv::Mat histHSorg, histHSeq;
    
    // Read the original image
    src = cv::imread("fruits.jpg");
    if ( !src.data ) {
        std::cout << "Cannot read the source image!" << std::endl;
    }

    // Separate image to 3 places (B, G, R)
    std::vector<cv::Mat> bgr_planes;
    cv::split(src, bgr_planes);

    // Display the result
    cv::namedWindow("Source Image", 0);
    cv::imshow("Source Image", src);

    // Calculate the histogram of the source image
    histImg = histogram_2D_calculation(src);

    // Display the histogram for each colour channel.
    cv::imshow("H-S Histogram", histImg);

    // Equalized image

    // Apply histogram equalization for each channel.
    std::ranges::for_each(bgr_planes, [] (cv::Mat& plane) {
        cv::equalizeHist(plane, plane);
    });

    // Merge the equalized channels into the equalized image.
    cv::merge(bgr_planes, imageEq);

    // Display the equalized image.
    cv::namedWindow("Equalized Image", 0);
    cv::imshow("Equalized Image", imageEq);

    // Calculate the 3D histogram for H and S channels.
    histImgEq = histogram_2D_calculation(imageEq);

    // Display the 2D histogram.
    cv::imshow("H-S Histogram Equalized", histImgEq);
    histHSorg = histogram_RG_calculation(src);
    histHSeq = histogram_RG_calculation(imageEq);

    // Apply the histogram comparision methods.
    for (int i = 0; i < 4; ++i) {
        const int compare_method = i;
        const double orig_orig = cv::compareHist(histHSorg, histHSorg, compare_method);
        const double orig_equ = cv::compareHist(histHSorg, histHSeq, compare_method);

        std::cout << std::format(
            " The method[{}]: Original-Original {}, Original-Equalized {}", compare_method, orig_orig, orig_equ) 
            << std::endl;
    } 

    std::cout << "Done!" << std::endl;

    cv::waitKey();
}