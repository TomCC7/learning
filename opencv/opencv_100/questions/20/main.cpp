/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 20 histogram
 * @date 2021-01-15
 */
#include "histogram/histogram.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
using std::cout, std::endl;
using namespace cv;

int main()
{
    Mat in = imread("imori_noise.jpg");
    Mat in_dark = imread("imori_dark.jpg");
    Mat histogram = get_histogram(in);
    Mat histogram_dark = get_histogram(in_dark);
    imshow("histogram", histogram);
    imshow("histogram dark", histogram_dark);
    imshow("origin", in);
    imwrite("answers/histogram.jpg", histogram_dark);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
