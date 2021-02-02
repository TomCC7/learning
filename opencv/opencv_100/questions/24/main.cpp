/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 24 Gamma Correction
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
 * @brief make GammaCorrection to the image
 * 
 * @param src 
 * @param dst 
 */
void GammaCorrection(const cv::Mat &src, cv::Mat &dst)
{
    dst = src.clone();
    auto src_ptr = src.ptr<const Vec3b>();
    auto dst_ptr = dst.ptr<Vec3b>();
    for (int i = 0; i < src.rows * src.cols; i++)
    {
        for (int c = 0; c < 3; c++) dst_ptr[i][c] = (uchar)(255 * pow((double)src_ptr[i][c] / 255, 1 / 2.2));
    }
}

int main()
{
    Mat in = imread("imori_gamma.jpg");
    Mat out;
    GammaCorrection(in, out);
    Mat his = get_histogram(out);
    imshow("gamma", out);
    imshow("origin", in);
    imshow("histogram", his);
    imwrite("answers/gamma.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
