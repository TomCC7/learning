/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 21 Histogram Normalization
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

/**
 * @brief Get the grey scale value based on bgr value
 *
 * @param bgr
 * @return uchar
 */
uchar get_grey_scale(const Vec3b &bgr)
{
    return 0.2126 * (float)bgr[2] + 0.7152 * (float)bgr[1] + 0.0722 * (float)bgr[0];
}

/**
 * @brief normalize histogram from [c,d] to [a,b]
 *
 * @param src
 * @param dst
 * @param c
 * @param d
 * @param a
 * @param b
 */
void HistogramNormalization(const cv::Mat &src, cv::Mat &dst, double a, double b, double c, double d)
{
    dst = cv::Mat(src.rows, src.cols, CV_8UC3);
    auto src_ptr = src.ptr<const cv::Vec3b>();
    auto dst_ptr = dst.ptr<cv::Vec3b>();
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            for (int ch = 0; ch < 3; ch++)
            {
                double ans = (b - a) / (d - c) * ((double)src_ptr[i * dst.cols + j][ch] - c) + a;
                ans = fmin(ans, 255);
                ans = fmax(ans, 0);
                dst_ptr[i * dst.cols + j][ch] = (uchar)ans;
            }
        }
    }
}

/**
 * @overload
 * @brief this will find cd
 * @param src
 * @param dst
 * @param a
 * @param b
 */
void HistogramNormalization(const cv::Mat &src, cv::Mat &dst, int a, int b)
{
    // find c d
    double c = 999, d = 0;
    auto src_ptr = src.ptr<const cv::Vec3b>();
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            uchar tmp = get_grey_scale(src_ptr[i * src.cols + j]);
            if ((double)tmp > d) d = (double)tmp;
            if ((double)tmp < c) c = (double)tmp;
        }
    }
    HistogramNormalization(src, dst, a, b, c, d);
}

int main()
{
    Mat in_dark = imread("imori_dark.jpg");
    Mat out,his;
    HistogramNormalization(in_dark, out, 0, 255);
    his = get_histogram(out);
    imshow("normorlized", out);
    imshow("origin", in_dark);
    imshow("histogram normorlized",his);
    imwrite("answers/normalized.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
