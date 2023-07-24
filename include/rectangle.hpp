#include <opencv2/opencv.hpp>
#include <string>
#include <random>
#include <vector>
#include "utils.hpp"

void createRectangles(cv::Mat& image, cv::Mat& targetImage, std::mt19937& generator, unsigned int times);