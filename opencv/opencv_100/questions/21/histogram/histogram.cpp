#include "histogram.hpp"
#include <opencv2/core/base.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat get_histogram(const cv::Mat &src_img)
{
    using namespace cv;
    Mat src_gray;
    // check image
    if (src_img.channels() == 3)
        cvtColor(src_img, src_gray, COLOR_BGR2GRAY);
    else
        src_gray = src_img;              // still reference
    CV_Assert(src_gray.channels() == 1); // gray scale check

    auto src_gray_ptr = src_gray.ptr<const uchar>();
    // get histogram values
    std::vector<uint> src(256, 0);
    uchar tmp;
    for (int i = 0; i < src_img.rows; i++)
    {
        for (int j = 0; j < src_img.cols; j++)
        {
            tmp = src_gray_ptr[i * src_img.cols + j];
            src[tmp]++;
        }
    }

    return get_histogram(src);
}

cv::Mat get_histogram(const std::vector<uint> &src)
{
    using namespace cv;
    const uint height{512}, width{512};
    CV_Assert(src.size() == 256); // check size
    cv::Mat graph = cv::Mat::zeros(height, width, CV_8UC1);
    // get max
    uint max = 0;
    for (uint i : src)
    {
        if (i > max) max = i;
    }
    // draw
    for (uint i = 0; i < 256; i++)
    {
        line(graph, Point2i(i * width / 256, height), Point2i(i * width / 256, height - src[i] * height / max),
             Scalar(255, 255, 255), 1);
    }
    return graph;
}