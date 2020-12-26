#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operation
namespace Artist
{
  int drawPoint(cv::Mat & frame, float,float);
  int drawRectangle(cv::Mat & frame,float,float,float,float);
  int drawLine(cv::Mat & frame,float,float,float,float);
};

#endif
