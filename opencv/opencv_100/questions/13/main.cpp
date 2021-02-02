/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 13 Min Max Filter
 * @date 2021-01-14
 * @note sb problem: use src instead of dst when calculating
 */
#include <cstdint>
#include <iostream>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
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
 * @brief Min Max filter based on standard 3*3 grid
 * @param src grey scale
 * @param dst
 */
void MinMaxFilter(const Mat &src, Mat &dst)
{
    CV_Assert(src.channels() == 1); // grey scale
    dst = src.clone();
    auto src_ptr = src.ptr<uchar>();
    auto dst_ptr = dst.ptr<uchar>();
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            uchar min = UINT8_MAX;
            uchar max = 0;
            for (int di = -1; di < 2; di++)
            {
                for (int dj = -1; dj < 2; dj++)
                {
                    // check out of range
                    if ((di + i) >= 0 && (dj + j) >= 0 && (di + i) < src.rows && (dj + j) < src.cols)
                    {
                        uchar val = src_ptr[(i + di) * src.cols + (j + dj)];
                        if (val > max) max = val;
                        if (val < min) min = val;
                    }
                }
            }
            dst_ptr[i * src.cols + j] = max - min;
        }
    }
}

int main()
{
    Mat in = imread("imori.jpg", IMREAD_COLOR);
    cvtColor(in, in, COLOR_BGR2GRAY);
    Mat out;
    MinMaxFilter(in, out);
    imshow("min max filter", out);
    imshow("origin", in);
    imwrite("min_max_filter.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}