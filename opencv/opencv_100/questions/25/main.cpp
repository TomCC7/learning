/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 25 Nearest-neighbor Interpolation
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
 * @brief adding pixels of image by just scaling...
 *
 * @param src
 * @param dst
 * @param a
 */
void NearestNeighborInterpolation(const cv::Mat &src, cv::Mat &dst, float a)
{
    CV_Assert(src.channels() == 3);
    dst = Mat((int)(a * (float)src.rows), (int)(a * (float)src.cols), CV_8UC3);
    auto src_ptr = src.ptr<const Vec3b>();
    auto dst_ptr = dst.ptr<Vec3b>();
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            for (int c = 0; c < 3; c++)
            {
                dst_ptr[i * dst.cols + j][c] = src_ptr[floor(i / a) * src.cols + floor(j / a)][c];
            }
        }
    }
}

int main()
{
    Mat in = imread("imori.jpg");
    Mat out;
    NearestNeighborInterpolation(in, out, 1.5);
    imshow("NearestNeighborInterpolation", out);
    imshow("origin", in);
    imwrite("answers/nearest_neightbor.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
