//
//  lab one.cpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//

#include <stdio.h>
#include "my_lib.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat gray_scale_img;
    cv::namedWindow("image.jpg");
    cv::imshow("image.jpg", img); 
    cv::waitKey(0);
    
    cv::cvtColor(img, gray_scale_img, cv::COLOR_BGR2GRAY);
    cv::imshow("gray_scale_image.jpg", gray_scale_img); 
    cv::waitKey(0);
    //cv::imwrite("/Users/nicolalorenzon/Library/Mobile Documents/com~apple~CloudDocs/Uni/CV/Code/lab two/image_grayscale.jpg", gray_scale_img); 
    
    cv::Mat min_ker_gimg = min_filter(gray_scale_img, 5);
    cv::imshow("min_ker_gimg.jpg", min_ker_gimg); 
    cv::waitKey(0);


    cv::Mat max_ker_gimg = max_filter(gray_scale_img, 5);
    cv::imshow("max_ker_gimg.jpg", max_ker_gimg); 
    cv::waitKey(0);

    cv::Mat median_ker_gimg = median_filter(gray_scale_img, 5);
    cv::imshow("median_ker_gimg.jpg", median_ker_gimg); 
    cv::waitKey(0);

    cv::Mat gaussian_ker_gimg = gaussian_filter(gray_scale_img, 5);
    cv::imshow("gaussian_filter.jpg", median_ker_gimg); 
    cv::waitKey(0);
    


    return 0;
}
