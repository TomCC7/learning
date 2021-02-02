/**
 * @file histogram.hpp
 * @author cc
 * @brief get histogram of an image
 * @version 0.1
 * @date 2021-01-15
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __HISTOGRAM__
#define __HISTOGRAM__
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

/**
 * @brief Get the histogram cv::Mat
 *
 * @param src vector consists of histogram values
 * @return cv::Mat containing histogram
 */
cv::Mat get_histogram(const std::vector<uint> &src);

/**
 * @overload
 * @param src_img input image
 * @return cv::Mat
 */
cv::Mat get_histogram(const cv::Mat &src_img);

#endif