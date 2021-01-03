#ifndef BERN_IMAGEVIEWPORT_H_
#define BERN_IMAGEVIEWPORT_H_

#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>

class ImageViewPort
{
 public:
  ImageViewPort(char * name, GtkWidget * parent_grid,int col, int row,
                GCallback clickedCallback, GCallback mouseMotionCallback, void * callback_data);                 
  GtkWidget * scroll;
  GtkWidget * frame;
  GtkWidget * drawing_area;
  cv::Mat * image; //TODO - use cv::mat, not cv::mat *

  static gboolean image_draw(GtkWidget * widget, cairo_t * cr, gpointer data);
 
};

#endif
