//
//  lab one.cpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const int LIGHT_ORANGE[3] = {11, 92, 132};
const int DARK_ORANGE[3] = {59, 172, 219};
const int BLUE[3] = {140, 54, 37};
const int MASK_COLOR[3] = {92, 37, 201};

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


Mat segment_with_masks(Mat img, const Mat mask[3]) {
	Mat help_img;
	vector<Mat> channels(3);
	help_img = img.clone();
	//cout<<"1\n";
	split(help_img, channels);
	
	cout<<"img.cols = " << img.cols << endl;
	cout<<"img.rows = " << img.rows << endl;
	cout<<"mask[0].cols = " << mask[0].cols << endl;
	cout<<"mask[0].rows = " << mask[0].rows << endl;
	cout<<"mask[1].cols = " << mask[1].cols << endl;
	cout<<"mask[1].rows = " << mask[1].rows << endl;
	cout<<"mask[2].cols = " << mask[2].cols << endl;
	cout<<"mask[2].rows = " << mask[2].rows << endl;
	

	
	for(int y = 0; y < img.cols; y++) {
		for(int x = 0; x < img.rows; x++) {
			cout << mask[0].at<int>(x,y);
			if((mask[0].at<uchar>(x,y) == 255) 
				|| (mask[1].at<uchar>(x,y) == 255) 
				|| (mask[2].at<uchar>(x,y) == 255)
			) {
				channels[0].at<uchar>(x,y) = MASK_COLOR[0];
				channels[1].at<uchar>(x,y) = MASK_COLOR[1];
				channels[2].at<uchar>(x,y) = MASK_COLOR[2];				 
			}
		}
	}
	merge(channels, help_img);
	return help_img;
}

int main(int argc, char** argv) {
    // read the image
    Mat img = imread(argv[1]);
	
	Mat help_img, segmented_image;
	Mat mask[3];

	
    // create the window
    namedWindow("image");
    namedWindow("mask1");
    namedWindow("mask2");
    namedWindow("mask3");

	img.convertTo(help_img, -1, 3, 10); //qui mettere val

	
	
	mask[0] = create_mask(img, LIGHT_ORANGE[0], LIGHT_ORANGE[1], LIGHT_ORANGE[2], 50);
	
	mask[1] = create_mask(img, DARK_ORANGE[0], DARK_ORANGE[1], DARK_ORANGE[2], 50);
	mask[2] = create_mask(help_img, BLUE[0], BLUE[1], BLUE[2], 50);

	segmented_image = segment_with_masks(img, mask);

    // display the image img in "image" window
    imshow("image", segmented_image); 
    imshow("mask1", mask[0]);
    imshow("mask2", mask[1]);
    imshow("mask3", mask[2]);
	
    waitKey(0);
    
    return 0;
}
