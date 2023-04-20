#include "my_lib.hpp"

cv::Mat min_filter(cv::Mat img, int dim) {
    int r = img.rows;
    int c = img.cols;
    uchar min;
    cv::Mat new_mat = img.clone();
    if(dim%2 == 0) {
        std::cout << "There's a problem with kernel dimension: Can't be even!";
    }
    else {
        for(int i = 1 + (dim-1)/2; i < r - (dim-1)/2 - 1; i++) {
            for(int j = 1 + (dim-1)/2; j < c - (dim-1)/2 - 1; j++) {
                min = img.at<uchar>(i, j);
                for(int kr = i - int((dim-1)/2); kr < i + int((dim-1)/2); kr++) {
                    for(int kc = j - int((dim-1)/2); kc < j + int((dim-1)/2); kc++) {
                        if(img.at<uchar>(kr, kc) < uchar(min)) {
                            min = uchar(img.at<uchar>(kr, kc));
                        }
                    }
                }
                new_mat.at<uchar>(i, j) = min;
            }
        }
    }
    return new_mat;
}
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

cv::Mat median_filter(cv::Mat img, int dim) {
    cv::Mat new_mat = img.clone();
    cv::medianBlur(img, new_mat, dim);
    return new_mat;
}

cv::Mat gaussian_filter(cv::Mat img, int dim) {
    cv::Mat new_mat = img.clone();
    cv::GaussianBlur(img, new_mat, cv::Size(dim, dim), 0);
    return new_mat;
}