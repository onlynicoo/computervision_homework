#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
int kernel_help = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*) {

  // Checks that kernel size is always odd
  if( ((kernel_help % 2) == 1) and (kernel_help >= 3) ) kernel_size = kernel_help;
  
  // blur and canny the image
  blur( src_gray, detected_edges, Size(3,3) );
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  imshow( window_name, detected_edges);
}

int main( int argc, char** argv )
{
  src = cv::imread(argv[1], IMREAD_COLOR);
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  namedWindow( window_name, WINDOW_AUTOSIZE );
  namedWindow( "original_image", WINDOW_AUTOSIZE );
  imshow( "original_image", src);
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  createTrackbar( "Ratio:", window_name, &ratio, 6,  CannyThreshold );
  createTrackbar( "Kernel size:", window_name, &kernel_help, 7, CannyThreshold);
  setTrackbarMin( "Ratio:", window_name, 1);
  setTrackbarMin( "Kernel size:", window_name, 3);
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}