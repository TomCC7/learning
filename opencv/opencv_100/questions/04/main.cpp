/**
 * @file main.cpp
 * @author cc
 * @brief  learn opencv 100 questions: 4
 * @date 2021-01-12
 * @method:  Otsu's Method to determine the threshold
 * If there is no valley one method of determining T is to minimize the total
 * variance within both classes.
 *
 */
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief Get the otsu threshold
 * @param src cv::Mat with CV_8UC1
 * @return uint
 */
uint get_otsu_threshold(const cv::Mat &src)
{
    double max = 0;
    uint t = 0;
    for (uint index = 0; index < 256; index++)
    {
        uint c0{0}, c1{0};   // count for 0 and 1
        double w0{0}, w1{0}; // w0 + w1 = 1, w0/c0 = w1/c1
        double m0{0}, m1{0}; // mean values
        for (int i = 0; i < src.rows; i++)
        {
            for (int j = 0; j < src.cols; j++)
            {
                uchar val = src.at<uchar>(i, j);
                if (val < index)
                {
                    m0 += val;
                    c0++;
                }
                else
                {
                    m1 += val;
                    c1++;
                }
            }
        }
        // get mean value
        m0 /= c0;
        m1 /= c1;
        // get w
        uint num_pix = src.rows * src.cols;
        w0 = (double)c0 / num_pix;
        w1 = (double)c1 / num_pix;
        double S = w0 * w1 * (m0 - m1) * (m0 - m1);
        if (S > max)
        {
            max = S;
            t = index;
        }
    }
    std::cout << "Max Value: " << max << std::endl;
    return t;
}

int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = cv::Mat(in.rows, in.cols, CV_8UC1);
    uchar tmp;
    for (int i = 0; i < in.rows; i++)
    {
        for (int j = 0; j < in.cols; j++)
        {
            out.at<uchar>(i, j) = 0.2126 * (float)in.at<cv::Vec3b>(i, j)[2] +
                                  0.7152 * (float)in.at<cv::Vec3b>(i, j)[1] + 0.0722 * (float)in.at<cv::Vec3b>(i, j)[0];
        }
    }

    uint thr_hold = get_otsu_threshold(out);
    std::cout << "Threshold: " << thr_hold << std::endl;
    for (int i = 0; i < in.rows; i++)
    {
        for (int j = 0; j < in.cols; j++)
        {
            tmp = out.at<uchar>(i, j);
            out.at<uchar>(i, j) = tmp > thr_hold ? 255 : 0;
        }
    }
    cv::imshow("test", out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}