/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 6
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
 * @brief convert pixel from 256 to 4
 * 
 * @param src input pixel val   
 * @return uchar 
 */
uchar u256to4(uchar src)
{
    if (src < 64)
        src = 32;
    else if (src < 128)
        src = 96;
    else if (src < 192)
        src = 160;
    else
        src = 224;
    return src;
}

/**
 * @brief reduce the color of src from 256^3 to 4^3 
 * @param src 
 */
void reduce_color(cv::Mat &src)
{
    cv::Vec3b *img = src.ptr<cv::Vec3b>();
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            cv::Vec3b tmp = img[i * src.rows + j];
            tmp[0] = u256to4(tmp[0]);
            tmp[1] = u256to4(tmp[1]);
            tmp[2] = u256to4(tmp[2]);
            img[i * src.rows + j] = tmp;
        }
    }
}

int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = in.clone();
    reduce_color(out);
    cv::imshow("color reverse", out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}