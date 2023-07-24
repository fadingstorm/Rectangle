#include "utils.hpp"

// Lower score is better
double calculateDifference(cv::Mat& image1, cv::Mat& image2) {
    int height {image1.rows};
    int width {image1.cols};
    double score {0.0};
    double maxDifference {255.0 * 3.0};

    for (int y {}; y < (height - 1); y++) {
        for (int x {}; x < (width - 1); x++) {

            // Find the difference for Blue, Green, and Red respectively
            score += std::abs(image1.at<cv::Vec3b>(y, x)[0] - image2.at<cv::Vec3b>(y, x)[0]);
            score += std::abs(image1.at<cv::Vec3b>(y, x)[1] - image2.at<cv::Vec3b>(y, x)[1]);
            score += std::abs(image1.at<cv::Vec3b>(y, x)[2] - image2.at<cv::Vec3b>(y, x)[2]);
        }
    }
    score = score / (height * width * maxDifference);
    return score;
}