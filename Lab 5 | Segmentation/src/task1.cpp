#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "filters.h"

using namespace cv;

Mat src, kernel = getStructuringElement(1, Size(5,5));
Mat preprocessed_img, thresholded_img;
int val = 1; 
const char* preprocessing_window_name = "preprocessed_img";
const char* thresholded_window_name = "thresholded_img";

static void Threshold(int, void*) {
  src.copyTo(preprocessed_img);

  // aumenta contrasto
  preprocessed_img.convertTo(preprocessed_img, -1, 6, 0); //qui mettere val

  // smooth
  Mat a;
  GaussianBlur(preprocessed_img, a, Size(5, 5), 70);
  bilateralFilter(a, preprocessed_img,5,75,75);

  dilate(preprocessed_img, preprocessed_img, kernel);
  erode(preprocessed_img, preprocessed_img, kernel);

  // smooth
  GaussianBlur(preprocessed_img, preprocessed_img, Size(5, 5), 50);
  imshow(preprocessing_window_name, preprocessed_img);

  threshold(preprocessed_img, thresholded_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
  threshold(preprocessed_img, thresholded_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
  dilate(thresholded_img, preprocessed_img, kernel);
  dilate(thresholded_img, preprocessed_img, kernel);
  erode(thresholded_img, preprocessed_img, kernel);
  erode(thresholded_img, preprocessed_img, kernel);
  imshow(thresholded_window_name, thresholded_img);
}

int main( int argc, char** argv )
{

  src = cv::imread(argv[1], CV_16UC1);
  src.copyTo(preprocessed_img);
  src.copyTo(thresholded_img);
  
  namedWindow( preprocessing_window_name, WINDOW_AUTOSIZE ); 
  namedWindow( thresholded_window_name, WINDOW_AUTOSIZE );  

  imshow(preprocessing_window_name, preprocessed_img);
  imshow(preprocessing_window_name, preprocessed_img);
  
  createTrackbar( "Val:", preprocessing_window_name, &val, 500, Threshold);  

  waitKey(0);
 
  return 0;
}