#ifndef IMAGE_MANAGER_H_
#define IMAGE_MANAGER_H_
//#include "bgui.h"
#include <opencv2/opencv.hpp>

class ImageManager
{
public:
 ImageManager(int,int);
 cv::Mat frame;
 cv::Mat scratchFrame;
 void clearFrame();
 void clearScratchFrame();
 void clearFrame(cv::Mat &);
 void resizeFrame(int,int);
 int width;
 int height;
}; 

#endif
