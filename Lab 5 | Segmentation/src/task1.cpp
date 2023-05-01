#include <iostream>
#include "../include/utilities_functions.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat src, kernel = getStructuringElement(1, Size(5,5));
Mat preprocessed_img, thresholded_img;
int val = 1; 
const uchar color = 0;
const char* preprocessing_window_name = "preprocessed_img";
const char* thresholded_window_name = "thresholded_img";

int main( int argc, char** argv ) {


  src = cv::imread(argv[1], CV_16UC1);
  src.copyTo(preprocessed_img);
  src.copyTo(thresholded_img);
  
  namedWindow( preprocessing_window_name, WINDOW_AUTOSIZE );
  namedWindow( thresholded_window_name, WINDOW_AUTOSIZE );
  
  // aumenta contrasto
  preprocessed_img.convertTo(preprocessed_img, -1, 6, 0);

  // smooth
  Mat support_mat;
  GaussianBlur(preprocessed_img, support_mat, Size(5, 5), 70);
  bilateralFilter(support_mat, preprocessed_img, 5, 75, 75);

  // remove noisy black dots
  dilate(preprocessed_img, preprocessed_img, kernel);
  erode(preprocessed_img, preprocessed_img, kernel);

  // smooth
  GaussianBlur(preprocessed_img, preprocessed_img, Size(5, 5), 50);
  imshow( preprocessing_window_name, preprocessed_img);

  // threshold 
  threshold(preprocessed_img, thresholded_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
  
  Mat final_image = merge_mask_to_img(src, thresholded_img, color);

  imshow(thresholded_window_name, final_image);

  waitKey(0);
 
  return 0;
}