#include "avgColor.hpp"

cv::Scalar calcAvgColor(std::string imagePath) {
    cv::Mat image {cv::imread(imagePath)};

    int rows {image.rows};
    int columns {image.cols};
    int pixels {rows * columns};
    
    int blueTotal {0}, greenTotal {0}, redTotal {0};

    // Get all the Blue, Green, and Red values of the image
    for (size_t y {0}; y < rows; y++) {
        for (size_t x {0}; x < columns; x++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            blueTotal += pixel[0];
            greenTotal += pixel[1];
            redTotal += pixel[2];
        }
    }

    int blueAvg {blueTotal / pixels};
    int greenAvg {greenTotal / pixels};
    int redAvg {redTotal / pixels};

    return cv::Scalar(blueAvg, greenAvg, redAvg);
}