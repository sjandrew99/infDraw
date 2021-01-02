#include "Artist.h"

int Artist::drawPoint(cv::Mat & frame, float x, float y)
{
   cv::circle(frame,cv::Point(x,y),1,cv::Scalar(0,0,0),-1);
   return 0;
}

//top-left and bottom-right
int Artist::drawRectangle(cv::Mat & frame,float x1,float y1,float x2,float y2)
{
 Artist::drawRectangle(frame,x1,y1,x2,y2,0,0,0,LINE_WIDTH);
 return 0;
}

int Artist::drawRectangle(cv::Mat & frame,float x1,float y1,float x2,float y2, unsigned int r, unsigned int g, unsigned int b,int width)
{
  cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y1), cv::Scalar(r,g,b), width);
  cv::line(frame, cv::Point(x1,y1), cv::Point(x1,y2), cv::Scalar(r,g,b), width);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x2,y1), cv::Scalar(r,g,b), width);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x1,y2), cv::Scalar(r,g,b), width);  
 return 0;
}



int Artist::drawLine(cv::Mat & frame,float x1,float y1,float x2,float y2)
{
 cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(0,0,0), LINE_WIDTH);
 return 0;
}