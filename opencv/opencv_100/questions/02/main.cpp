#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat in = cv::imread("imori.jpg");
    cv::Mat out = cv::Mat(in.rows, in.cols, CV_8UC1);
    for (int i = 0; i < in.rows; i++)
    {
        for (int j = 0; j < in.cols; j++)
        {
            out.at<uchar>(i, j) = 0.2126 * (float)in.at<cv::Vec3b>(i, j)[2] +
                                  0.7152 * (float)in.at<cv::Vec3b>(i, j)[1] + 0.0722 * (float)in.at<cv::Vec3b>(i, j)[0];
        }
    }
    cv::imshow("test", out);
    cv::waitKey(0);
    cv::destroyAllWindows();
}