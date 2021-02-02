/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 10
 * @date 2021-01-13
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
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
 * @brief get the median value from vector
 *
 * @param src
 * @return uchar
 */
uchar median_value(std::vector<uchar> src)
{
    std::sort(src.begin(), src.end());
    if (src.size() % 2 == 0) // even
        return (src[src.size() / 2] + src[src.size() / 2 - 1]) / 2;
    else
        return src[src.size() / 2];
}

/**
 * @brief median filter based on standard 3*3 grid
 *
 * @param src
 * @param dst
 */
void MedianFilter(const Mat &src, Mat &dst)
{
    dst = src.clone();
    auto img = dst.ptr<Vec3b>();
    std::vector<uchar> values;
    values.reserve(9);                 // reserve space
    for (int i = 0; i < src.rows; i++) // rows
    {
        for (int j = 0; j < src.cols; j++) // cols
        {
            for (int c = 0; c < src.channels(); c++) // channels
            {
                values.clear();                 // clear value
                for (int di = -1; di < 2; di++) // drows
                {
                    for (int dj = -1; dj < 2; dj++) // dcols
                    {
                        // check out of range
                        if ((di + i) >= 0 && (dj + j) >= 0 && (di + i) < src.rows && (dj + j) < src.cols)
                        {
                            values.push_back(img[(i + di) * src.cols + (j + dj)][c]);
                        }
                    }
                }
                img[i * src.cols + j][c] = median_value(values);
            }
        }
    }
}

int main()
{
    Mat in = imread("imori_noise.jpg");
    Mat out;
    MedianFilter(in, out);
    imshow("median filter", out);
    imwrite("median_filter.jpg", out);
    waitKey(0);
    destroyAllWindows();
}