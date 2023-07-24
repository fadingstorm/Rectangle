#include <opencv2/opencv.hpp>
#include <string>

cv::Scalar calcAvgColor(std::string imagePath);
cv::Scalar calcAvgColorInArea(const cv::Mat image, int y, int x, int width, int height);