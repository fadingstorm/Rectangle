#include <opencv2/opencv.hpp>
#include <iostream>
#include "avgColor.hpp"
#include "rectangle.hpp"

int main() {
    const std::string TARGET_IMAGE {"/Users/garethmcclellan/Documents/Rectangle/images/target.jpg"};

    // seed the randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    cv::Mat image = cv::imread(TARGET_IMAGE, cv::IMREAD_COLOR);

    int imageWidth = image.cols;
    int imageHeight = image.rows;

    cv::Scalar backgroundColor {calcAvgColor(TARGET_IMAGE)};

    cv::Mat generatedImage(imageHeight, imageWidth, CV_8UC3, backgroundColor);

    createRectangles(generatedImage, TARGET_IMAGE, gen, 1000);

    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "All done." << std::endl;
    return 0;
}