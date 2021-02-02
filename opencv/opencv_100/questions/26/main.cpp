/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 26 Bilinear Interpolation
 * @date 2021-01-15
 */
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
 * @brief perform bilinear interpolation
 *
 * @param src
 * @param dst
 * @param a
 */
void BilinearInterpolation(const cv::Mat &src, cv::Mat &dst, double a)
{
    CV_Assert(src.channels() == 3);
    dst = Mat::zeros((int)(a * (double)src.rows), (int)(a * (double)src.cols), CV_8UC3);
    auto src_ptr = src.ptr<const Vec3b>();
    auto dst_ptr = dst.ptr<Vec3b>();
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            int i0 = floor((double)i / a);
            int j0 = floor((double)j / a);
            fmin(i0, src.rows);
            fmin(j0, src.cols);
            double di0 = (double)i / a - i0;
            double dj0 = (double)j / a - j0;
            for (int c = 0; c < 3; c++)
            {
                dst_ptr[i * dst.cols + j][c] = (uchar)(src_ptr[i0 * src.cols + j0][c] * (1 - di0) * (1 - dj0) +
                                                       src_ptr[(i0 + 1) * src.cols + j0][c] * di0 * (1 - dj0) +
                                                       src_ptr[i0 * src.cols + j0 + 1][c] * (1 - di0) * dj0 +
                                                       src_ptr[(i0 + 1) * src.rows + j0 + 1][c] * di0 * dj0);
            }
        }
    }
}

int main()
{
    Mat in = imread("imori.jpg");
    Mat out;
    BilinearInterpolation(in, out, 1.5);
    imshow("Bilinear", out);
    imshow("origin", in);
    imwrite("answers/bilinear.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
