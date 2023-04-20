#include <iostream>
#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges, destination;
int lowThreshold = 280;
const int max_lowThreshold = 450;
int ratio = 2;
int kernel_size = 3;
int kernel_help = 3;
int hough_parameter = 100;
const char* window_name = "Edge Map";
int den = 51;
int min_radius = 5;
int max_radius = 22;

Point lineLineIntersection(Point A, Point B, Point C, Point D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1*(A.x) + b1*(A.y);
 
    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2*(C.x)+ b2*(C.y);
 
    double determinant = a1*b2 - a2*b1;
 
    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return Point(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return Point(x, y);
    }
}


static void CannyThreshold(int, void*) {

  // Checks that kernel size is always odd
  if( ((kernel_help % 2) == 1) and (kernel_help >= 3) ) kernel_size = kernel_help;
  
  // blur and canny the image
  blur( src_gray, detected_edges, Size(3,3) );
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  src.copyTo( destination );
  
  // Standard Hough Line Transform
  std::vector<Vec2f> lines; // will hold the results of the detection
  HoughLines(detected_edges, lines, 1, CV_PI/den, hough_parameter, 0, 0 ); // runs the actual detection
  // Find the points of the lines
  Point points[4];
  for( size_t i = 0; i < lines.size(); i++ )
  {
    float rho = lines[i][0], theta = lines[i][1];
    Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;
    pt1.x = cvRound(x0 + 1000*(-b));
    pt1.y = cvRound(y0 + 1000*(a));
    pt2.x = cvRound(x0 - 1000*(-b));
    pt2.y = cvRound(y0 - 1000*(a));
    if( i < 2){
      points[i*2] = pt1;
      points[i*2+1] = pt2;
    }
  }
  // Draw the polygon
  std::vector<Point> intersection_points = {};
  if(lines.size() == 2) {
    intersection_points.push_back(lineLineIntersection(points[0],points[1],points[2],points[3]));
    intersection_points.push_back(lineLineIntersection(points[0],points[1],Point(0,destination.rows),Point(1,destination.rows)));
    intersection_points.push_back(lineLineIntersection(points[2],points[3],Point(0,destination.rows),Point(1,destination.rows)));
    fillPoly(destination, std::vector<std::vector<Point>> {intersection_points}, Scalar(0, 0, 255));
  }
  
  // Find the circle
  std::vector<Vec3f> circles;
  HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1,
                src_gray.rows/16,
                100, 30, 
                min_radius, 
                max_radius 
  );

  // Draw the circle
  for( size_t i = 0; i < circles.size(); i++ ) {
      Vec3i c = circles[i];
      cv::Point center = Point(c[0], c[1]);
      // circle outline
      int radius = c[2];
      circle( destination, center, radius, Scalar(0,255,0), -1);
  }
  
  // Plot the image
  imshow(window_name, destination);
  imshow("canny_image", detected_edges);
}

// Prints the parameters value
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
  if  ( event == EVENT_RBUTTONDOWN ) {
    std::cout << "lowThreshold = " << lowThreshold << std::endl;
    std::cout << "ratio = " << ratio << std::endl;
    std::cout << "kernel_size = " << kernel_size << std::endl;
    std::cout << "hough_parameter = " << hough_parameter << std::endl;
    std::cout << "min_radius = " << min_radius << std::endl;
    std::cout << "max_radius = " << max_radius << std::endl;
    
  }
}


int main( int argc, char** argv )
{
  src = cv::imread(argv[1], IMREAD_COLOR);
  dst.create( src.size(), src.type());
  cvtColor( src, src_gray, COLOR_BGR2GRAY);
  namedWindow( window_name, WINDOW_AUTOSIZE );
  namedWindow( "canny_image", WINDOW_AUTOSIZE );
  createTrackbar( "min_radius:", window_name, &min_radius, 180, CannyThreshold);
  createTrackbar( "max_radius:", window_name, &max_radius, 180, CannyThreshold);
  setMouseCallback("Edge Map", CallBackFunc, (void*)NULL); 
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}