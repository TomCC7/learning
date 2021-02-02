/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 5
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

uint umax3(uint i1, uint i2, uint i3)
{
    return MAX(i1, MAX(i2, i3));
}

uint umin3(uint i1, uint i2, uint i3)
{
    return MIN(i1, MIN(i2, i3));
}

/**
 * @brief get hsv value from bgr value
 * @param bgr bgr value
 * @return cv::Vec3d  hsv value
 */
cv::Vec3d bgr2hsv(const cv::Vec3b &bgr)
{
    uchar max = umax3(bgr[0], bgr[1], bgr[2]);
    uchar min = umin3(bgr[0], bgr[1], bgr[2]);
    cv::Vec3d hsv;

    if (min == max)
    {
        hsv[0] = 0;
    }
    else if (min == bgr[0])
    {
        hsv[0] = 60 * (double)(bgr[1] - bgr[2]) / (max - min) + 60;
    }
    else if (min == bgr[1])
    {
        hsv[0] = 60 * (double)(bgr[2] - bgr[0]) / (max - min) + 300;
    }
    else if (min == bgr[2])
    {
        hsv[0] = 60 * (double)(bgr[0] - bgr[1]) / (max - min) + 180;
    }
    hsv[1] = max - min;
    hsv[2] = max;
    return hsv;
}

/**
 * @brief convert hsv to bgr
 * @param hsv
 * @return cv::Vec3b
 */
cv::Vec3b hsv2bgr(const cv::Vec3d &hsv)
{
    double c = hsv[1];       // c = s
    double h_ = hsv[0] / 60; // h' = h/60
    double x = c * (1 - abs(fmod(h_, 2) - 1));
    cv::Vec3b bgr(hsv[2] - c, hsv[2] - c, hsv[2] - c);
    uint h_i = floor(h_);
    switch (h_i)
    {
    case 0:
        bgr[1] += x;
        bgr[2] += c;
        break;
    case 1:
        bgr[1] += c;
        bgr[2] += x;
        break;
    case 2:
        bgr[0] += x;
        bgr[1] += c;
        break;
    case 3:
        bgr[0] = c;
        bgr[1] = x;
        break;
    case 4:
        bgr[0] = c;
        bgr[2] = x;
        break;
    case 5:
        bgr[0] = c;
        bgr[2] = x;
        break;
    }
    return bgr;
}

void reverse_color(cv::Mat &src)
{
    int rows = src.rows;
    int cols = src.cols;
    cv::Vec3b *img = src.ptr<cv::Vec3b>();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cv::Vec3d hsv = bgr2hsv(img[i * rows + j]);
            hsv[0] += 180;
            hsv[0] = fmod(hsv[0], 360); // in case overflow
            img[i * rows + j] = hsv2bgr(hsv);
        }
    }
}
int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = in.clone();
    reverse_color(out);
    cv::imshow("H Reverse", out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}