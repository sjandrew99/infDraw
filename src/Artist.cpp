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

//specify the top left and bottom right
int Artist::drawRectangle(cv::Mat & frame,float x1,float y1,float x2,float y2, unsigned int r, unsigned int g, unsigned int b,int width)
{
  cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y1), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x1,y1), cv::Point(x1,y2), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x2,y1), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x1,y2), cv::Scalar(r,g,b), width, cv::LINE_AA);  
 return 0;
}

//specify all four corners (for a rotated rectangle)
int Artist::drawRectangle(cv::Mat & frame,float x1,float y1,float x2,float y2, 
                                          float x3, float y3, float x4, float y4, unsigned int r, unsigned int g, unsigned int b,int width)
{
  cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x2,y2), cv::Point(x3,y3), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x3,y3), cv::Point(x4,y4), cv::Scalar(r,g,b), width, cv::LINE_AA);
  cv::line(frame, cv::Point(x4,y4), cv::Point(x1,y1), cv::Scalar(r,g,b), width, cv::LINE_AA);  
 return 0;
}



int Artist::drawLine(cv::Mat & frame,float x1,float y1,float x2,float y2)
{
 cv::line(frame, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(0,0,0), LINE_WIDTH, cv::LINE_AA);
 return 0;
}

int Artist::drawArrowLine(cv::Mat & frame,float x1,float y1,float x2,float y2,float tipLength)
{
 cv::arrowedLine(frame, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(0,0,0), LINE_WIDTH,cv::LINE_AA,0,tipLength);
 return 0;
}

int Artist::drawText(cv::Mat & frame, float x, float y, std::string text)
{                                                //fontFace, fontScale, color, thickness, lineType
 //lineTyoe enum: https://docs.opencv.org/master/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777
 cv::putText(frame, text.c_str(), cv::Point(x,y),cv::FONT_HERSHEY_TRIPLEX,.5,cv::Scalar(0,0,0),1); //TODO - find a function that can render rotated text
 return 0;
}