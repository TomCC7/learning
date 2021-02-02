#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

cv::Mat swap_channel(const cv::Mat &src) {
  cv::Mat out = src.clone();
  int height = out.rows;
  int width = out.cols;
  unsigned char tmp;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      tmp = out.at<cv::Vec3b>(i, j)[0];
      out.at<cv::Vec3b>(i, j)[0] = out.at<cv::Vec3b>(i, j)[2];
      out.at<cv::Vec3b>(i, j)[2] = tmp;
    }
  }
  return out;
}

int main() {
  cv::Mat in = cv::imread("imori.jpg");
  cv::Mat out = swap_channel(in);
  cv::imshow("origin",in);
  cv::imshow("out",out);
  cv::waitKey(0);
  cv::destroyAllWindows();
}