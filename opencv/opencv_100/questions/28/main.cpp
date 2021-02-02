/**
 * @file main.cpp
 * @author cc
 * @brief OpenCV 100Wen: 28 Afine Transformations-move
 * @date 2021-01-18
 */
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
using std::cout, std::endl;
using namespace cv;

/**
 * @brief make affine transformation
 *
 * @param src
 * @param dst
 * @param a
 * @param b
 * @param c
 * @param d
 * @param tx
 * @param ty
 */
void affine(const cv::Mat &src, cv::Mat &dst, double a, double b, double c, double d, double tx, double ty)
{
    // get height and width
    int width = src.cols;
    int height = src.rows;
    int channel = src.channels();

    // get detriment
    double det = a * d - b * c;

    // Resize width and height
    int resized_width = (int)(width * a);
    int resized_height = (int)(height * d);

    // other parameters
    int x_before, y_before;
    double dx, dy, wx, wy, w_sum;
    double val;
    int _x, _y;

    dst = cv::Mat::zeros(resized_height, resized_width, CV_8UC3);
    auto src_ptr = src.ptr<const Vec3b>();
    auto dst_ptr = dst.ptr<Vec3b>();

    // Affine transformation
    // traverse new image because src not correspond uniquely
    for (int i = 0; i < resized_height; i++)
    {
        for (int j = 0; j < resized_width; j++)
        {

            // get original position x
            x_before = (int)((d * j - b * i) / det - tx);

            if ((x_before < 0) || (x_before >= width)) { continue; }

            // get original position y
            y_before = (int)((-c * j + a * i) / det - ty);

            if ((y_before < 0) || (y_before >= height)) { continue; }

            // assign pixel to new position
            for (int c = 0; c < channel; c++)
            {
                dst_ptr[i * dst.cols + j][c] = src_ptr[y_before * src.cols + x_before][c];
            }
        }
    }
}

void move(const cv::Mat &src, cv::Mat &dst, double tx, double ty) { affine(src, dst, 1, 0, 0, 1, tx, ty); }

int main()
{
    Mat in = imread("imori.jpg");
    Mat out;
    move(in, out, 30, -30);
    imshow("affine-move", out);
    imshow("origin", in);
    imwrite("answers/affine_move.jpg", out);
    while (waitKey(0) != 27) {}
    destroyAllWindows();
}
