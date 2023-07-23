#include "rectangle.hpp"
#include "avgColor.hpp"

void createRectangles(cv::Mat& image, const std::string targetImagePath, std::mt19937& generator, unsigned int times) {
    for (size_t i {}; i < times; i++) {
        
        // The top left corner of the rectangle
        int yLow {0};
        int yHigh {image.rows - 1};
        int xLow {0};
        int xHigh {image.cols - 1};
        
        std::uniform_int_distribution<int> yCornerGen(yLow, yHigh);
        std::uniform_int_distribution<int> xCornerGen(xLow, xHigh);

        int rectangleCornerY {yCornerGen(generator)};
        int rectangleCornerX {xCornerGen(generator)};

        // The dimensions of the rectangle
        std::uniform_int_distribution<int> yDim(1, yHigh - rectangleCornerY);
        std::uniform_int_distribution<int> xDim(1, xHigh - rectangleCornerX);

        int rectangleHeight {yDim(generator)};
        int rectangleWidth {xDim(generator)};

        cv::Scalar avgColorInArea {calcAvgColorInArea(targetImagePath, rectangleCornerY, rectangleCornerX, rectangleWidth, rectangleHeight)};

        for (int y {rectangleCornerY}; y < (rectangleCornerY + rectangleHeight); y++) {
            for (int x {rectangleCornerX}; x < (rectangleCornerX + rectangleWidth); x++) {
                cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);

                // change each pixel in the box
                pixel[0] = avgColorInArea[0];
                pixel[1] = avgColorInArea[1];
                pixel[2] = avgColorInArea[2];
            }
        }


        cv::imshow("Generated Image", image);
    }
}