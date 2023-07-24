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

    for (size_t i {}; i < 500; i++) {
        std::cout << "Shape " << i + 1 << " of " << "500" << std::endl;
        createRectangles(generatedImage, image, gen, 20);
    }
    cv::imshow("Generated Image", generatedImage);
    std::cout << "DONE!!!" << std::endl;
    

    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "All done." << std::endl;
    return 0;
}