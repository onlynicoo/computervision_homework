//
//  lab one.cpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//
#include<iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

const int histSize = 256;

void drawHistogram(cv::Mat& ,cv::Mat& g_hist,cv::Mat& r_hist);

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat gray_scale_img;
    cv::namedWindow("image.jpg");
    cv::imshow("image.jpg", img); 
    cv::waitKey(0);
    cv::cvtColor(img, gray_scale_img, cv::COLOR_BGR2GRAY);
    cv::imshow("gray_scale_image.jpg", gray_scale_img); 
    cv::waitKey(0);
 
    cv::Mat hist;
    
    

    return 0;
}

void drawHistogram(cv::Mat& b_hist,cv::Mat& g_hist,cv::Mat& r_hist) {

    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());

    for (int i = 1; i < histSize; i++) {
      cv::line(
          histImage,
          cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
          cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
          cv::Scalar(255, 0, 0), 2, 8, 0);
      cv::line(
          histImage,
          cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
          cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
          cv::Scalar(0, 255, 0), 2, 8, 0);
      cv::line(
          histImage,
          cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
          cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
          cv::Scalar(0, 0, 255), 2, 8, 0);
    }