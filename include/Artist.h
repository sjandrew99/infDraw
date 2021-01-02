#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operation
#include "common.h"
namespace Artist
{
  int drawPoint(cv::Mat & frame, float,float);
  int drawRectangle(cv::Mat & frame,float,float,float,float); //draws black
  int drawRectangle(cv::Mat & frame,float,float,float,float, unsigned int, unsigned int, unsigned int);
  int drawLine(cv::Mat & frame,float,float,float,float);
};

#endif
