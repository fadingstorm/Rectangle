#include <opencv2/opencv.hpp>
#include <iostream>
#include "avgColor.hpp"

int main() {
    const std::string TARGET_IMAGE {"/Users/garethmcclellan/Documents/Rectangle/images/target.jpg"};

    cv::Mat image = cv::imread(TARGET_IMAGE, cv::IMREAD_COLOR);

    int imageWidth = image.cols;
    int imageHeight = image.rows;

    cv::Scalar backgroundColor {calcAvgColor(TARGET_IMAGE)};

    cv::Mat generatedImage(imageHeight, imageWidth, CV_8UC3, backgroundColor);

    cv::imshow("Blank Image", generatedImage);

    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "All done." << std::endl;
    return 0;
}