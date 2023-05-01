//
//  lab one.cpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//
#include <stdio.h>
#include <iostream>
#include "../include/utilities_functions.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int LIGHT_ORANGE[3] = {11, 92, 132};
const int DARK_ORANGE[3] = {59, 172, 219};
const int BLUE[3] = {140, 54, 37};
const int MASK_COLOR[3] = {92, 37, 201};
const char* window_name = "segmented image";


// returns the matrix of the mask
Mat create_mask(Mat& mat, int m_B, int m_G, int m_R, int t) {
    Mat help_img = mat;
    Mat mask = Mat::zeros(Size(help_img.cols, help_img.rows), CV_8UC1);

    // iterate over rows
    for(int i = 0; i < help_img.rows; i++) {
        // iterate over columns
        for(int j = 0; j < help_img.cols; j++) {
            
            // check wether the gray values of the three channels are more distant of a threshold with respect to the mean
            if ( (abs(int(help_img.at<Vec3b>(i,j)[0]) - m_B) <= t) &&
                    (abs(int(help_img.at<Vec3b>(i,j)[1]) - m_G) <= t) &&
                    (abs(int(help_img.at<Vec3b>(i,j)[2]) - m_R) <= t) 
                ) mask.at<uchar>(i, j) = 255;
            else mask.at<uchar>(i, j) = 0;
        }
    }
    return mask;
}

int main(int argc, char** argv) {
    // read the image
    Mat src = imread(argv[1]);
	
	Mat help_img, segmented_image;
	Mat mask[3];

	
    // create the window
    namedWindow(window_name, WINDOW_AUTOSIZE); 

	src.convertTo(contrast_img, -1, 3, 10);	
	
	mask[0] = create_mask(src, LIGHT_ORANGE[0], LIGHT_ORANGE[1], LIGHT_ORANGE[2], 50);
	
	mask[1] = create_mask(src, DARK_ORANGE[0], DARK_ORANGE[1], DARK_ORANGE[2], 50);
	mask[2] = create_mask(contrast_img, BLUE[0], BLUE[1], BLUE[2], 50);

	segmented_image = segment_with_masks(src, mask, MASK_COLOR);

    // display the image img in "image" window
    imshow(window_name, segmented_image);
	
    waitKey(0);
    
    return 0;
}
