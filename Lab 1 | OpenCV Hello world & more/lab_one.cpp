//
//  lab one.cpp
//  lab one
//
//  Created by Nicola Lorenzon on 06/03/23.
//

#include "lab_one.hpp"
#include <opencv2/highgui.hpp>
int main(int argc, char** argv)
{
cv::Mat img = cv::imread(argv[1]);
cv::namedWindow("Example 1");
cv::imshow("Example 1", img); cv::waitKey(0);
return 0;
}
