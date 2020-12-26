#include "Artist.h"

int Artist::drawPoint(cv::Mat & frame, float x, float y)
{
   cv::circle(frame,cv::Point(x,y),1,cv::Scalar(0,0,0),-1);
}

int Artist::drawRectangle(cv::Mat & frame,float x1,float y1,float x2,float y2)
{
  cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y1), cv::Scalar(0,0,0), 2);
  cv::line(frame, cv::Point(x1,y1), cv::Point(x1,y2), cv::Scalar(0,0,0), 2);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x2,y1), cv::Scalar(0,0,0), 2);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x1,y2), cv::Scalar(0,0,0), 2);
}

int Artist::drawLine(cv::Mat & frame,float x1,float y1,float x2,float y2)
{
 cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(0,0,0), 2);

}