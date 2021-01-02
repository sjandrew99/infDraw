#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operation
#include "common.h"
namespace Artist
{
  int drawPoint(cv::Mat & frame, float,float);
  int drawRectangle(cv::Mat & frame,float,float,float,float); //draws black
  int drawRectangle(cv::Mat & frame,float,float,float,float, unsigned int, unsigned int, unsigned int,int width);
  int drawRectangle(cv::Mat & frame,float,float,float,float, 
                                    float,float,float,float, 
                                    unsigned int, unsigned int, unsigned int,int width); //allows specifying all four points (8 coords) to draw a rotated rect
  int drawLine(cv::Mat & frame,float,float,float,float);
  int drawText(cv::Mat & frame, float,float,std::string);
};

#endif
