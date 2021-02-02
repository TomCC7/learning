/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 8
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

/**
 * @brief Get the grey scale value based on bgr value
 *
 * @param bgr
 * @return uchar
 */
uchar get_grey_scale(const cv::Vec3b &bgr)
{
    return 0.2126 * (float)bgr[2] + 0.7152 * (float)bgr[1] + 0.0722 * (float)bgr[0];
}

/**
 * @brief pool the image by max value
 *
 * @param dst
 * @param grid_size
 */
void max_pooling(cv::Mat &dst, const uint grid_size = 8)
{
    uint step = dst.rows / grid_size;
    auto dst_ptr = dst.ptr<cv::Vec3b>();
    int rows = dst.rows;
    int cols{dst.cols};
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cv::Vec<uint, 3> max{0, 0, 0};
            for (int si = i * step; si < i * step + step; si++)
            {
                for (int sj = j * step; sj < j * step + step; sj++)
                {
                    if (get_grey_scale(dst_ptr[si * rows + sj]) > get_grey_scale(max)) max = dst_ptr[si * cols + sj];
                }
            }
            for (int si = i * step; si < i * step + step; si++)
            {
                for (int sj = j * step; sj < j * step + step; sj++) { dst_ptr[si * cols + sj] = max; }
            }
        }
    }
}

int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = in.clone();
    max_pooling(out, 16);
    cv::imshow("max pooling", out);
    cv::imwrite("max_out.jpg", out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}