//
//  lab one.hpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//
#ifndef MY_LIB
#define MY_LIB

#include <stdio.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat min_filter(cv::Mat img, int dim);
cv::Mat max_filter(cv::Mat img, int dim);
cv::Mat median_filter(cv::Mat img, int dim);
cv::Mat gaussian_filter(cv::Mat img, int dim);

#endif // MY_LIB //