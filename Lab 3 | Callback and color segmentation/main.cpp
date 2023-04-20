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

int COLOR[3] = {92, 37, 201};

// returns the maximum between two integers
int max(int a, int b) {
    if(a < b) return b;
    return a;
}

// returns the mininum between two integers
int min(int a, int b) {
    if(a > b) return b;
    return a;
}

// returns the integer mean of the nine neighbor pixels
int mean_of_neighbor(Mat& mat, int x, int y, int z) {
    Mat help_img = mat;
    int res = 0;
    for(int i = max(x-1, 0); i <= min(x+1, help_img.rows); i++) {
        for(int j = max(y-1, 0); j <= min(y+1, help_img.cols); j++) {
            res += int(help_img.at<Vec3b>(i,j)[z]/9);
        }
    }
    return res;
}

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

// returns the matrix of the segmented image 
Mat segment_given_color(Mat& mat, int m_B, int m_G, int m_R, int t) {
    Mat help_img = mat;
    Mat new_img = help_img.clone();
    
    // iterate over rows
    for(int i = 0; i < help_img.rows; i++) {
        // iterate over columns
        for(int j = 0; j < help_img.cols; j++) {

            // check wether the gray values of the three channels are more distant of a threshold with respect to the mean
            if ( (abs(int(help_img.at<Vec3b>(i,j)[0]) - m_B) <= t) &&
                    (abs(int(help_img.at<Vec3b>(i,j)[1]) - m_G) <= t) &&
                    (abs(int(help_img.at<Vec3b>(i,j)[2]) - m_R) <= t) 
                ) {
                    new_img.at<Vec3b>(i, j)[0] = COLOR[0];
                    new_img.at<Vec3b>(i, j)[1] = COLOR[1];
                    new_img.at<Vec3b>(i, j)[2] = COLOR[2];
                }
            else {
                new_img.at<Vec3b>(i, j)[0] = int(help_img.at<Vec3b>(i,j)[0]);
                new_img.at<Vec3b>(i, j)[1] = int(help_img.at<Vec3b>(i,j)[1]);
                new_img.at<Vec3b>(i, j)[2] = int(help_img.at<Vec3b>(i,j)[2]);
            }
        }
    }
    return new_img;
}

// function called when an actiokn occurs
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {

    // check if the left button has been clicked
    if  ( event == EVENT_LBUTTONDOWN )
    {
        // cast the general type pointer to Mat* pointer in order to use it later
        Mat help_img = *(Mat *) userdata;
        Mat mask_img;
        Mat new_image;

        cout << "Left button of the mouse is clicked - position (column, row) (" << x << ", " << y << ")" << endl;

        cout << "Task 2:" << endl;
        cout << "Pixel B = " << int(help_img.at<Vec3b>(y,x)[0]) << endl;
        cout << "Pixel G = " << int(help_img.at<Vec3b>(y,x)[1]) << endl;
        cout << "Pixel R = " << int(help_img.at<Vec3b>(y,x)[2]) << endl;
        cout << "----------" << endl;
        cout << "Task 3:" << endl;
        int m_B = mean_of_neighbor(help_img, y, x, 0);
        int m_G = mean_of_neighbor(help_img, y, x, 1);
        int m_R = mean_of_neighbor(help_img, y, x, 2);
        
        cout << "Mean B = " << m_B << endl;
        cout << "Mean G = " << m_G << endl;
        cout << "Mean R = " << m_R << endl;
        cout << "----------" << endl;
        mask_img = create_mask(help_img, m_B, m_G, m_R, 50);
        namedWindow("mask_image");
        imshow("mask_image", mask_img); 
        cout << "Mask created" << endl;
        cout << "----------" << endl;
        new_image = segment_given_color(help_img, m_B, m_G, m_R, 50);
        namedWindow("new_image");
        imshow("new_image", new_image); 
        cout << "New image created" << endl;
        cout << "----------" << endl;
    }
}


int main(int argc, char** argv)
{
    // read the image
    Mat img = imread(argv[1]);

    // create the window
    namedWindow("image");

    //set the callback function for any mouse event
    setMouseCallback("image", CallBackFunc, (void*)&img);

    // display the image img in "image" window
    imshow("image", img); 

    // wait for a key button
    waitKey(0);
    
    return 0;
}
