/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 19
 * @date 2021-01-14
 */
#include <cmath>
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
 * @brief gaussian filter based on standard 3*3 grid
 *
 * @param src
 * @param dst
 */
void GaussianFilter(const Mat &src, Mat &dst)
{
    const Vec<Vec3b, 3> filter{{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}; // filter matrix
    const int KERNEL_SUM = 16;
    dst = src.clone();
    auto img = dst.ptr<Vec3b>();
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            for (int c = 0; c < src.channels(); c++) // channels
            {
                uint v = 0;
                for (int di = -1; di < 2; di++) // drows
                {
                    for (int dj = -1; dj < 2; dj++) // dcols
                    {
                        // check out of range
                        if ((di + i) >= 0 && (dj + j) >= 0 && (di + i) < src.rows && (dj + j) < src.cols)
                        {
                            v += img[(i + di) * src.cols + (j + dj)][c] * filter[di + 1][dj + 1];
                        }
                    }
                }
                v /= KERNEL_SUM;
                img[i * src.cols + j][c] = v;
            }
        }
    }
}

/**
 * @brief LoGFilter
 *
 * @param src
 * @param dst
 * @param kernel_size odd
 * @param sigma
 */
void LoGFilter(const Mat &src, Mat &dst, const uint kernel_size = 5, double sigma = 3)
{
    // checks
    CV_Assert(src.channels() == 1);  // gray scale allowed
    CV_Assert(kernel_size % 2 == 1); // odd number
    int pad = floor(kernel_size / 2);
    double kernel_sum = 0;
    // prepare filter
    double filter[kernel_size][kernel_size]; // filter matrix
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            int _i = i - pad;
            int _j = j - pad;
            filter[i][j] = ((_i * _i + _j * _j) - sigma * sigma) * exp(-(_i * _i + _j * _j) / (2 * sigma * sigma)) /
                           (2 * M_PI * pow(sigma, 6));
            kernel_sum += filter[i][j];
        }
    }
    // unify
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            filter[i][j] /= kernel_sum;
            cout << filter[i][j] << endl;
        }
    }

    dst = src.clone();
    auto src_ptr = src.ptr<uchar>();
    auto dst_ptr = dst.ptr<uchar>();
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            double v = 0;
            for (int di = -pad; di < pad + 1; di++) // drows
            {
                for (int dj = -pad; dj < pad + 1; dj++) // dcols
                {
                    // check out of range
                    if ((di + i) >= 0 && (dj + j) >= 0 && (di + i) < src.rows && (dj + j) < src.cols)
                    {
                        v += (double)src_ptr[(i + di) * src.cols + (j + dj)] * filter[di + pad][dj + pad];
                    }
                }
            }
            fmax(v, 0);
            fmin(v, 255);
            dst_ptr[i * src.cols + j] = (uchar)v;
        }
    }
}

int main()
{
    Mat in = imread("imori_noise.jpg");
    Mat gauss, gray, out;
    GaussianFilter(in, gauss);
    cvtColor(gauss, gray, COLOR_BGR2GRAY);
    LoGFilter(gray, out);
    imshow("LoG filter", out);
    imshow("gray", gray);
    imwrite("log.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
