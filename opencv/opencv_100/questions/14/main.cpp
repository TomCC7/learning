/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 14 Differential Filter
 * @date 2021-01-14
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
 * @brief Differential Filter based on 3*3 grid
 *
 * @param src
 * @param dst
 * @param vertical bool default false
 */
void DifferentialFilter(const Mat &src, Mat &dst, bool vertical = false)
{
    CV_Assert(src.channels() == 1);
    dst = src.clone();
    auto src_ptr = src.ptr<uchar>();
    auto dst_ptr = dst.ptr<uchar>();
    int offset = -1;
    if (vertical) offset = -src.cols;
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            int val{0};
            // check out of range
            if ((vertical && i > 0) || (!vertical && j > 0))
            {
                val = (int)src_ptr[i * src.cols + j] - (int)src_ptr[i * src.cols + j + offset]; // incase of overflow
            }
            if (val < 0) val = 0;
            dst_ptr[i * src.cols + j] = (uchar)val;
        }
    }
}

int main()
{
    Mat in = imread("imori.jpg", IMREAD_COLOR);
    cvtColor(in, in, COLOR_BGR2GRAY);
    Mat out;
    DifferentialFilter(in, out);
    imshow("differential filter", out);
    imshow("origin", in);
    imwrite("diff_filter.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}