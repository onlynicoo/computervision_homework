#include <stdio.h>
#include <iostream>
#include "../include/utilities_functions.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

const char* window_name = "segmented image";

int main(int argc, char** argv) {

	Mat input_image = imread(argv[1]);
	
    Mat blurred_img;
    
    namedWindow( window_name, WINDOW_AUTOSIZE ); 
    
    GaussianBlur(input_image, blurred_img, Size(9, 9), 80);
	
    int Clusters = 3;
	Mat clustered_image = K_Means(blurred_img, Clusters);

	imshow(window_name, clustered_image);
    
    waitKey();
	return 0;
}