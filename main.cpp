#include <opencv2/opencv.hpp>
#include <iostream>
#include "avgColor.hpp"
#include "rectangle.hpp"

int main() {
    const std::string TARGET_IMAGE {"/Users/garethmcclellan/Documents/Rectangle/images/D56A4136-B8CD-41A5-A964-6F0554607FC3.jpg"};

    // seed the randomness
    std::random_device rd;
    std::mt19937 gen(rd());

    cv::Mat image = cv::imread(TARGET_IMAGE, cv::IMREAD_COLOR);

    // Downscale the image if needed
    // Ensure that it is at least 1080p
    int targetWidth = 1920;
    int targetHeight = 1080;
    if (image.cols > targetWidth || image.rows > targetHeight) {
        double scale = std::min(static_cast<double>(targetWidth) / image.cols, static_cast<double>(targetHeight) / image.rows);
        cv::resize(image, image, cv::Size(), scale, scale);
    }

    int imageWidth = image.cols;
    int imageHeight = image.rows;

    cv::Scalar backgroundColor {calcAvgColor(TARGET_IMAGE)};

    cv::Mat generatedImage(imageHeight, imageWidth, CV_8UC3, backgroundColor);

    for (size_t i {}; i < 1000; i++) {
        std::cout << "Shape " << i + 1 << " of " << "1000" << std::endl;
        createRectangles(generatedImage, image, gen, 200);
        
        cv::imshow("Generated Image", generatedImage);
        int key = cv::waitKey(50);
        if (key == 'q')
            break;

    }
    
    std::cout << "DONE!!!" << std::endl;
    

    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "All done." << std::endl;
    return 0;
}