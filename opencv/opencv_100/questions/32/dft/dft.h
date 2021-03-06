/**
 * @file dft.h
 * @brief dft lib
 * @version 0.1
 * @date 2021-01-18
 */
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat getDftMat(const cv::Mat &src);