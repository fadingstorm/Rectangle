#include <opencv2/opencv.hpp>
#include <string>
#include <random>

void createRectangles(cv::Mat& image, const std::string targetImagePath, std::mt19937& generator, unsigned int times);