#include "../include/utilities_functions.h"

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

cv::Mat merge_mask_to_img(const cv::Mat img, const cv::Mat mask, const uchar color) {

    cv::Mat help_img = img.clone();

    std::vector<cv::Mat> channels(1);
    
    for(int y = 0; y < help_img.cols; y++) {
        for(int x = 0; x < help_img.rows; x++) {
            if(mask.at<uchar>(x,y) == 0) {
                help_img.at<uchar>(x,y) = 255;
            }
        }
    }
    return help_img;
}

cv::Mat segment_with_masks(const cv::Mat img, const cv::Mat mask[3], const int mask_color[]) {
	cv::Mat help_img;
	std::vector<cv::Mat> channels(3);
	help_img = img.clone();
    
	split(help_img, channels);

	for(int y = 0; y < img.cols; y++) {
		for(int x = 0; x < img.rows; x++) {
			if((mask[0].at<uchar>(x,y) == 255) 
				|| (mask[1].at<uchar>(x,y) == 255) 
				|| (mask[2].at<uchar>(x,y) == 255)
			) {
				channels[0].at<uchar>(x,y) = mask_color[0];
				channels[1].at<uchar>(x,y) = mask_color[1];
				channels[2].at<uchar>(x,y) = mask_color[2];				 
			}
		}
	}
	merge(channels, help_img);
	return help_img;
}


cv::Mat K_Means(cv::Mat img, int K) {
    
	cv::Mat labels;
	cv::Mat centers;
    cv::Mat gray_mask;

	cv::Mat samples(img.rows * img.cols, img.channels(), CV_32F);
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			for (int z = 0; z < img.channels(); z++)
				if (img.channels() == 3) {
					samples.at<float>(y + x * img.rows, z) = img.at<cv::Vec3b>(y, x)[z];
				}
				else {
					samples.at<float>(y + x * img.rows, z) = img.at<uchar>(y, x);
				}

	int attempts = 5;
	cv::kmeans(samples, K, labels, cv::TermCriteria(cv::TermCriteria::MAX_ITER|cv::TermCriteria::EPS, 10000, 0.0001), attempts, cv::KMEANS_PP_CENTERS, centers);

    cv::cvtColor(img, gray_mask, cv::COLOR_BGR2GRAY);
	
    for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * img.rows, 0);
            if (cluster_idx > 2) {
                std::cout<< cluster_idx << std::endl;
            }
            gray_mask.at<uchar>(y, x) = cluster_idx * 75;
		}
	return gray_mask;
}