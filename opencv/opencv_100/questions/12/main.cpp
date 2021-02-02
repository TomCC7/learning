/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 12 Motion Filter
 * @date 2021-01-13
 */
#include <iostream>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
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
 * @brief Motion filter based on standard 3*3 grid
 * 1/3  0   0
 * 0   1/3  0
 * 0   0   1/3
 *
 * @param src
 * @param dst
 */
void MotionFilter(const Mat &src, Mat &dst)
{
    dst = src.clone();
    auto img = dst.ptr<Vec3b>();
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            for (int c = 0; c < src.channels(); c++) // channels
            {
                uint v = 0;
                for (int d = -1; d < 2; d++) // d for diagnal line
                {
                    // check out of range
                    if ((d + i) >= 0 && (d + j) >= 0 && (d + i) < src.rows && (d + j) < src.cols)
                    {
                        v += img[(i + d) * src.cols + (j + d)][c];
                    }
                }
                v /= 3;
                img[i * src.cols + j][c] = v;
            }
        }
    }
}

int main()
{
    Mat in = imread("imori_noise.jpg");
    Mat out;
    MotionFilter(in, out);
    imshow("motion filter", out);
    imwrite("motion_filter.jpg", out);
    while (waitKey(0) != 27)
    {
    }
    destroyAllWindows();
}