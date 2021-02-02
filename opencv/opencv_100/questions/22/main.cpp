/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 22 Histogram Operation
 * @date 2021-01-15
 */
#include "histogram/histogram.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/hal/interface.h>
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
 * @brief convert image to given mean value and standard deviation
 *
 * @param src
 * @param dst
 * @param m mean value
 * @param s standard deviation
 */
void HistogramOperation(const cv::Mat &src, cv::Mat &dst, double m, double s)
{
    Mat gray;
    if (src.channels() == 1)
        gray = src;
    else
        cvtColor(src, gray, COLOR_BGR2GRAY);
    // get mean
    double m0 = 0;
    auto src_ptr = src.ptr<const Vec3b>();
    auto gray_ptr = gray.ptr<const uchar>();
    for (int i = 0; i < gray.rows * gray.cols; i++) { m0 += (double)gray_ptr[i]; }
    m0 /= (double)(gray.rows * gray.cols);
    // standard deviation
    double s0 = 0;
    for (int i = 0; i < gray.rows * gray.cols; i++) { s0 += (double)((gray_ptr[i] - m0) * (gray_ptr[i] - m0)); }
    s0 /= (double)(gray.rows * gray.cols - 1);
    s0 = sqrt(s0);
    cout << m0 << ',' << s0 << endl;
    // converting
    dst = Mat(src.rows, src.cols, CV_8UC3);
    auto dst_ptr = dst.ptr<Vec3b>();
    for (int i = 0; i < src.rows * src.cols; i++)
    {
        for (int c = 0; c < 3; c++)
        {
            double tmp = (s / s0 * ((double)src_ptr[i][c] - m0) + m);
            fmax(0, tmp);
            fmin(255, tmp);
            dst_ptr[i][c] = (uchar)tmp;
        }
    }
}

int main()
{
    Mat in_dark = imread("imori_dark.jpg");
    Mat out;
    HistogramOperation(in_dark, out, 128, 52);
    Mat his = get_histogram(out);
    imshow("operated", out);
    imshow("origin", in_dark);
    imshow("histogram", his);
    imwrite("answers/operated.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
