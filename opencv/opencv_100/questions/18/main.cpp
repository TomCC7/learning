/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 18
 * @date 2021-01-14
 */
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
 * @brief emboss filter based on standard 3*3 grid
 *
 * @param src
 * @param dst
 * @param vertical bool
 */
void EmbossFilter(const Mat &src, Mat &dst)
{
    CV_Assert(src.channels() == 1);
    Vec<Vec3i, 3> filter = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}}; // filter matrix
    dst = src.clone();
    auto src_ptr = src.ptr<uchar>();
    auto dst_ptr = dst.ptr<uchar>();
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            int v = 0;
            for (int di = -1; di < 2; di++) // drows
            {
                for (int dj = -1; dj < 2; dj++) // dcols
                {
                    // check out of range
                    if ((di + i) >= 0 && (dj + j) >= 0 && (di + i) < src.rows && (dj + j) < src.cols)
                    {
                        v += src_ptr[(i + di) * src.cols + (j + dj)] * filter[di + 1][dj + 1];
                    }
                }
            }
            if (v < 0) v = 0;
            if (v > 255) v = 255;
            dst_ptr[i * src.cols + j] = (uchar)v;
        }
    }
}

int main()
{
    Mat in = imread("imori.jpg");
    cvtColor(in, in, COLOR_BGR2GRAY);
    Mat out;
    EmbossFilter(in, out);
    imshow("Emboss filter", out);
    imshow("gray", in);
    imwrite("emboss.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}