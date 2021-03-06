#include "imageManager.h"
ImageManager::ImageManager(int width, int height)
{ 
 frame.create(height,width,CV_8UC3);
 this->height = height;
 this->width = width;
 clearFrame(); 
}

void ImageManager::clearFrame()
{
 clearFrame(this->frame);
}

void ImageManager::clearScratchFrame()
{
 clearFrame(this->scratchFrame);
}

void ImageManager::clearFrame(cv::Mat & _frame)
{
 /*cv::Mat_<cv::Vec3b> frame_ = _frame;
 for (int i=0; i<height; i++)
 {
  for (int j=0; j<width; j++)
  {
   frame_(i,j)[0] = 255;  
   frame_(i,j)[1] = 255;  
   frame_(i,j)[2] = 255;  
  }
 }*/
 typedef cv::Point3_<uint8_t> Pixel;
 _frame.forEach<Pixel>([](Pixel &p, const int * position) -> void 
 {
  p.x=255;
  p.y=255;
  p.z=255;
 }
 );
}

void ImageManager::cache()
{
 frame.copyTo(scratchFrame);
}
void ImageManager::pop()
{
 scratchFrame.copyTo(frame);
}

void ImageManager::resizeFrame(int width, int height)
{
 //copyTo
 this->width = width; this->height = height;
 frame.create(height, width, CV_8UC3);
}