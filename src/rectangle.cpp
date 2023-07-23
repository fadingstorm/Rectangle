#include "rectangle.hpp"
#include "avgColor.hpp"

// One generation
void createRectangles(cv::Mat& image, const std::string targetImagePath, std::mt19937& generator, unsigned int times) {
    cv::Mat targetImage {cv::imread(targetImagePath)};

    std::vector<double> rectangleScores;

    // The vector containing the information of every rectangle generated
    std::vector<std::vector<int>> rectangleInfo;
    /*
        [0] will be the upper left corner (y coord)
        [1] will be the upper left corner (x coord)
        [2] will be the height
        [3] will be the width

        [4] will be the BLUE value
        [5] will be the GREEN value
        [6] will be the RED value
    */

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

        double difference {calculateDifference(image, targetImage)};

        int blue {static_cast<int>(avgColorInArea[0] + 0.5)};
        int green {static_cast<int>(avgColorInArea[1] + 0.5)};
        int red {static_cast<int>(avgColorInArea[2] + 0.5)};


        std::vector<int> currentRectangleInfo = {rectangleCornerY, rectangleCornerX, rectangleHeight, rectangleWidth, blue, green, red};

        rectangleScores.push_back(difference);
        rectangleInfo.push_back(currentRectangleInfo);

    }
    cv::imshow("Generated Image", image);
}