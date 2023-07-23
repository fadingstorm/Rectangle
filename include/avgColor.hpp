#include <opencv2/opencv.hpp>
#include <string>

cv::Scalar calcAvgColor(std::string imagePath);
cv::Scalar calcAvgColorInArea(const std::string imagePath, int y, int x, int width, int height);