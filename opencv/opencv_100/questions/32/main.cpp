/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 32 fourier transformation
 * @date 2021-01-18
 */
#include "dft/dft.h"
#include <complex>
#include <iostream>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// Main
int main(int argc, const char *argv[])
{
    CV_Assert(argc == 2);
    cv::Mat in = cv::imread(argv[1]);
    cv::cvtColor(in, in, 6);
    cv::Mat dft_mat = getDftMat(in);
    cv::imshow("in", in);
    cv::imshow("dft", dft_mat);
    while (cv::waitKey() != 27) {}
    cv::destroyAllWindows();
}
