#ifndef UTILITIES_FUNCTION
#define UTILITIES_FUNCTION
//

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
cv::Mat max_filter(cv::Mat img, int dim);
cv::Mat merge_mask_to_img(const cv::Mat img, const cv::Mat mask, const uchar color);
cv::Mat segment_with_masks(const cv::Mat img, const cv::Mat mask[3], const int mask_color[]);
cv::Mat K_Means(cv::Mat img, int K);

//
#endif // UTILITIES_FUNCTION //d