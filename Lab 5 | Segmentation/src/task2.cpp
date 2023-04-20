#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat src, kernel = getStructuringElement(1, Size(5,5));
Mat preprocessed_img, thresholded_img;
int val = 1; 
const char* preprocessing_window_name = "preprocessed_img";
const char* thresholded_window_name = "thresholded_img";


cv::Mat max_filter(cv::Mat img, int dim) {
    int r = img.rows;
    int c = img.cols;
    uchar max;
    cv::Mat new_mat = img.clone();
    if(dim%2 == 0) {
        std::cout << "There's a problem with kernel dimension: Can't be even!";
    }
    else {
        for(int i = 1 + (dim-1)/2; i < r - (dim-1)/2 - 1; i++) {
            for(int j = 1 + (dim-1)/2; j < c - (dim-1)/2 - 1; j++) {
                max = img.at<uchar>(i, j);
                for(int kr = i - int((dim-1)/2); kr < i + int((dim-1)/2); kr++) {
                    for(int kc = j - int((dim-1)/2); kc < j + int((dim-1)/2); kc++) {
                        if(img.at<uchar>(kr, kc) > uchar(max)) {
                            max = uchar(img.at<uchar>(kr, kc));
                        }
                    }
                }
                new_mat.at<uchar>(i, j) = max;
            }
        }
    }
    return new_mat;
}

static void Threshold(int, void*) {

  src.copyTo(preprocessed_img);
  
  // aumenta contrasto
  preprocessed_img.convertTo(preprocessed_img, -1, 6, 0); //qui mettere val
  
  // smooth
  Mat a;
  GaussianBlur(preprocessed_img, a, Size(5, 5), 70);
  bilateralFilter(a, preprocessed_img, 5, 75, 75);

  //imshow("prima", preprocessed_img);

  dilate(preprocessed_img, preprocessed_img, kernel);
  erode(preprocessed_img, preprocessed_img, kernel);

  //std::cout<<preprocessed_img;
  //imshow("dopo", preprocessed_img);
  
  // max
  //preprocessed_img = max_filter(preprocessed_img, 5);

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
  //namedWindow( "prima", WINDOW_AUTOSIZE ); 
  //namedWindow( "dopo", WINDOW_AUTOSIZE );  
  imshow(preprocessing_window_name, preprocessed_img);
  imshow(preprocessing_window_name, preprocessed_img);
  
  createTrackbar( "Val:", preprocessing_window_name, &val, 500, Threshold);

  waitKey(0);
 
  return 0;
}