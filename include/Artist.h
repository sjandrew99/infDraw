#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operations
class Artist
{
 public: 
  static int drawPoint(cv::Mat & frame, float,float);
  static int drawRectangle(cv::Mat & frame,float,float,float,float);
  static int drawLine(cv::Mat & frame,float,float,float,float);
};

#endif
