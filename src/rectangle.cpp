#include "rectangle.hpp"
#include <iostream>
#include "avgColor.hpp"

// One generation
void createRectangles(cv::Mat& image, cv::Mat& targetImage, std::mt19937& generator, unsigned int times) {

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

    // The top left corner of the rectangle
    int yLow {0};
    int yHigh {image.rows - 1};
    int xLow {0};
    int xHigh {image.cols - 1};

    // Calculate difference...
    double difference {calculateDifference(image, targetImage)};
    
    for (size_t i {}; i < times; i++) {
        
        std::uniform_int_distribution<int> yCornerGen(yLow, yHigh);
        std::uniform_int_distribution<int> xCornerGen(xLow, xHigh);

        int rectangleCornerY {yCornerGen(generator)};
        int rectangleCornerX {xCornerGen(generator)};

        // The dimensions of the rectangle
        std::uniform_int_distribution<int> yDim(1, yHigh - rectangleCornerY);
        std::uniform_int_distribution<int> xDim(1, xHigh - rectangleCornerX);

        int rectangleHeight {yDim(generator)};
        int rectangleWidth {xDim(generator)};

        cv::Scalar avgColorInArea {calcAvgColorInArea(targetImage, rectangleCornerY, rectangleCornerX, rectangleWidth, rectangleHeight)};

        int blue {static_cast<int>(avgColorInArea[0] + 0.5)};
        int green {static_cast<int>(avgColorInArea[1] + 0.5)};
        int red {static_cast<int>(avgColorInArea[2] + 0.5)};


        std::vector<int> currentRectangleInfo = {rectangleCornerY, rectangleCornerX, rectangleHeight, rectangleWidth, blue, green, red};

        rectangleScores.push_back(difference);
        rectangleInfo.push_back(currentRectangleInfo);
    }
    
    size_t bestFit {0}; // The index of the best score
        
    for (size_t i = 1; i < rectangleScores.size(); ++i) { // Find the index of the rectangle with the lowest score
        if (rectangleScores[i] < bestFit) {
            bestFit = i;
        }
    }
    std::vector<int> bestRectangle {rectangleInfo[bestFit]};

    int bestCornerY {bestRectangle[0]};
    int bestCornerX {bestRectangle[1]};
    int bestHeight {bestRectangle[2]};
    int bestWidth {bestRectangle[3]};

    int bestBlue {bestRectangle[4]};
    int bestGreen {bestRectangle[5]};
    int bestRed {bestRectangle[6]};

    for (int y {bestCornerY}; y < (bestCornerY + bestHeight); y++) {
        for (int x {bestCornerX}; x < (bestCornerX + bestWidth); x++) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);

            // change each pixel in the box
            pixel[0] = bestBlue;
            pixel[1] = bestGreen;
            pixel[2] = bestRed;
        }
    }
}