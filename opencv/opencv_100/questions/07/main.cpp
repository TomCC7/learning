/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 7
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
 * @brief make average pooling based on grid size
 * 
 * @param dst change in place
 * @param grid_size how much grids
 */
void average_pooling(cv::Mat &dst, const uint grid_size = 8)
{
    uint step = dst.rows / grid_size;
    auto dst_ptr = dst.ptr<cv::Vec3b>();
    int rows = dst.rows;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            cv::Vec<uint, 3> avg{0, 0, 0};
            for (int si = i * step; si < i * step + step; si++)
            {
                for (int sj = j * step; sj < j * step + step; sj++)
                {
                    avg += dst_ptr[si * rows + sj];
                }
            }
            avg = avg / (int)(step * step);
            for (int si = i * step; si < i * step + step; si++)
            {
                for (int sj = j * step; sj < j * step + step; sj++)
                {
                    dst_ptr[si * rows + sj] = avg;
                }
            }
        }
    }
}

int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = in.clone();
    average_pooling(out,16);
    cv::imshow("average pooling", out);
    cv::imwrite("avg_out.jpg",out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}