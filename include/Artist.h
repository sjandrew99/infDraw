#ifndef ARTIST_H_
#define ARTIST_H_
#include <opencv2/opencv.hpp>
//handles drawing operations
class Artist
{
 int drawRectangle(cv::Mat & frame);
 int drawLine(cv::Mat & frame);
};

#endif
