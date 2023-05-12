#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace cv;
using namespace std;
//using namespace cv::xfeatures2d;

const char* window_name = "window";

/**
 cercare prima homograpy con ransac
 se a draw matches passo la mask presa da homography aloora salta le corrispondenzd scrause
 
*/


std::vector<DMatch> ransac(std::vector<KeyPoint> first_img_keypoints,std::vector<KeyPoint> second_img_keypoints, std::vector<DMatch> matches) {
  // Define RANSAC parameters
  int max_iterations = 5000;
  double distance_threshold = 1000.0;

  // Loop over iterations
  int best_num_inliers = 0;
  Mat best_H;
  for (int i = 0; i < max_iterations; i++) {
      // Randomly select four matches
      std::vector<Point2f> pts1, pts2;
      for (int j = 0; j < 4; j++) {
          int idx = rand() % matches.size();
          pts1.push_back(first_img_keypoints[matches[idx].queryIdx].pt);
          pts2.push_back(second_img_keypoints[matches[idx].trainIdx].pt);
      }

      // Compute homography matrix using four matches
      Mat mask;
      Mat H = findHomography(pts1, pts2, mask, RANSAC);

      // Count number of inliers
      int num_inliers = 0;
      //for (auto& match : matches) {
        for (int i = 0; i < matches.size(); i++) {
        if(mask.at<uchar>(i)) {
            
            Point2f pt1 = first_img_keypoints[matches[i].queryIdx].pt;
            Point2f pt2 = second_img_keypoints[matches[i].trainIdx].pt;
            

            std::vector<Point2f> pt1_transformed(1);
            perspectiveTransform(std::vector<Point2f>{pt1}, pt1_transformed, H);
            double dist = norm(pt1_transformed[0] - pt2);
            if (dist < distance_threshold) {
                num_inliers++;
            }
        }
      }

      // Update best match
      if (num_inliers > best_num_inliers) {
          best_num_inliers = num_inliers;
          best_H = H;
      }
  }

    // Compute final set of inlier matches
    std::vector<DMatch> inlier_matches;
        for (int i = 0; i < matches.size(); i++) {
        if(mask.at<uchar>(i)) {
            Point2f pt1 = first_img_keypoints[matches[i].queryIdx].pt;
            Point2f pt2 = second_img_keypoints[matches[i].trainIdx].pt;
            std::vector<Point2f> pt1_transformed(1);
            std::vector<Point2f> pt1_vector{Point2f(pt1.x, pt1.y)};
            cv::perspectiveTransform(pt1_vector, pt1_transformed, best_H);
            double dist = norm(pt1_transformed[1] - pt2);
            if (dist < distance_threshold) {
                inlier_matches.push_back(match);
            }
        }
    }
  return inlier_matches;
}
int main()
{
    // Load the image
    Mat first_img = imread("../images/all_souls_000006.jpg");
    Mat second_img = imread("../images/all_souls_000002.jpg");

    // Convert the image to grayscale
    Mat first_gray_img, second_gray_img;
    cvtColor(first_img, first_gray_img, COLOR_BGR2RGB);
    cvtColor(second_img, second_gray_img, COLOR_BGR2RGB);

    // Create a SIFT detector
    Ptr<FeatureDetector> detector = SIFT::create();

    // Detect keypoints in the image
    std::vector<KeyPoint> first_img_keypoints, second_img_keypoints;
    detector->detect(first_gray_img, first_img_keypoints);
    detector->detect(second_gray_img, second_img_keypoints);

    // Calculate SIFT descriptors for the keypoints
    Mat first_img_descriptors, second_img_descriptors;
    Ptr<DescriptorExtractor> extractor = SIFT::create();
    extractor->compute(first_img, first_img_keypoints, first_img_descriptors);
    extractor->compute(second_img, second_img_keypoints, second_img_descriptors);

    // Create a Brute-Force matcher and match the features
    BFMatcher matcher(NORM_L2);
    std::vector<DMatch> matches;
    matcher.match(first_img_descriptors, second_img_descriptors, matches);

    
    // Apply the distance ratio test to select only good matches
    std::vector<DMatch> good_matches;
    float distance_ratio_threshold = 0.35; // adjust this threshold as needed

    for (int i = 0; i < matches.size(); i++) {
        DMatch best_match = matches[i];
        DMatch second_best_match = matches[i+1];

        float distance_ratio = best_match.distance / second_best_match.distance;

        if (distance_ratio < distance_ratio_threshold) {
            good_matches.push_back(best_match);
        }
    }

    // ransac method
    std::vector<DMatch> ransac_matches = ransac(first_img_keypoints, second_img_keypoints, good_matches);

    // Draw the matches on the images
    Mat img_matches;
    drawMatches(first_img, first_img_keypoints, second_img, second_img_keypoints, ransac_matches, img_matches);

    // Show the result
    imshow("SIFT matches", img_matches);
    waitKey(0);


    return 0;
}