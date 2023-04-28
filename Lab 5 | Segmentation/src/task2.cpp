#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat K_Means(Mat Input, int K);

int main(int argc, char** argv) {

    const char* window_name = "window";
	Mat input_image = imread(argv[1]);
    Mat blurred_img;
    
    namedWindow( window_name, WINDOW_AUTOSIZE ); 
    namedWindow( "asdf", WINDOW_AUTOSIZE );  
	
    cout << "Height: " << input_image.rows << ", Width: " << input_image.rows << ", Channels: " << input_image.channels() << endl;

    GaussianBlur(input_image, blurred_img, Size(9, 9), 80);
	
    int Clusters = 3;
	Mat clustered_image = K_Means(blurred_img, Clusters);


	imshow(window_name, clustered_image);
    imshow("asdf", blurred_img);
	
    waitKey();
	return 0;
}

Mat K_Means(Mat img, int K) {
	Mat labels;
	Mat centers;
    Mat gray_mask;

	Mat samples(img.rows * img.cols, img.channels(), CV_32F);
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			for (int z = 0; z < img.channels(); z++)
				if (img.channels() == 3) {
					samples.at<float>(y + x * img.rows, z) = img.at<Vec3b>(y, x)[z];
				}
				else {
					samples.at<float>(y + x * img.rows, z) = img.at<uchar>(y, x);
				}

	int attempts = 5;
	kmeans(samples, K, labels, TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

    cvtColor(img, gray_mask, COLOR_BGR2GRAY);
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * img.rows, 0);
            if (cluster_idx > 2) {
                std::cout<< cluster_idx << std::endl;
            }
            gray_mask.at<uchar>(y, x) = cluster_idx * 75;
		}
	

    //imshow("clustered image", new_image);
	return gray_mask;
}