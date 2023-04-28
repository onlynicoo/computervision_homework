#include "filters.h"

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