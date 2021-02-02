#include "dft.h"
#include <opencv2/core/base.hpp>

cv::Mat getDftMat(const cv::Mat &src)
{
    using namespace cv;

    CV_Assert(src.channels() == 1);
    Mat padded; //以0填充输入图像矩阵
    int m = getOptimalDFTSize(src.rows);
    int n = getOptimalDFTSize(src.cols);

    //填充输入图像I，输入矩阵为padded，上方和左方不做填充处理
    copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;

    merge(planes, 2, complexI); //将planes融合合并成一个多通道数组complexI

    dft(complexI, complexI); //进行傅里叶变换

    //计算幅值，转换到对数尺度(logarithmic scale)
    //=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                    // planes[0] = Re(DFT(I),planes[1] = Im(DFT(I))
                                                //即planes[0]为实部,planes[1]为虚部
    magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
    Mat out = planes[0];

    out += Scalar::all(1);
    log(out, out); //转换到对数尺度(logarithmic scale)

    //如果有奇数行或列，则对频谱进行裁剪
    out = out(Rect(0, 0, out.cols & -2, out.rows & -2));
    //重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = out.cols / 2;
    int cy = out.rows / 2;

    Mat q0(out, Rect(0, 0, cx, cy));   //左上角图像划定ROI区域
    Mat q1(out, Rect(cx, 0, cx, cy));  //右上角图像
    Mat q2(out, Rect(0, cy, cx, cy));  //左下角图像
    Mat q3(out, Rect(cx, cy, cx, cy)); //右下角图像

    //变换左上角和右下角象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
    normalize(out, out, 0, 1, NORM_MINMAX);
    return out;
}