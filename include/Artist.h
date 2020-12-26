#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operations
class Artist
{
 public: 
 static int drawRectangle(cv::Mat & frame,float,float,float,float);
 int drawLine(cv::Mat & frame);
};

#endif
