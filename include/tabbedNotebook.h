#ifndef TABBED_NOTEBOOK_H_
#define TABBED_NOTEBOOK_H_
#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <vector>

#include "controlPanel.h"
#include "imageViewPort.h"
#include "imageManager.h"
//#include "Drawable.h"
#include "Artist.h"
class Drawable;
class TabbedNotebook; //forward declare 
class Tab
{
  public:
  Tab(TabbedNotebook * parent);
  GtkWidget * grid;
  ControlPanel * controlPanelTop;
  ControlPanel * controlPanelRight;
  ControlPanel * controlPanelBottom;
  ControlPanel * controlPanelLeft;
  ControlPanel * controlPanelLookup(int idx);
  ImageViewPort * imageViewPort; 
  int set_image(cv::Mat * image);
  TabbedNotebook * parent;
  ImageManager * imgMgr;
  GtkWidget * objectList;
  //Artist * artist;
  std::vector<Drawable*> drawables;
  //std::vector<> clickablePoints
  //std::vector<int> drawableTypes; 
  //int addDrawable(int which);
  int addRectangle(float x1,float y1,float x2, float y2);
  int addLine(float x1,float y1,float x2, float y2);
  void drawAll();
  void clear();
};

class BGui;
class TabbedNotebook
{
 public:
  TabbedNotebook(BGui * parent, GtkWidget *,int,int);
  int addTab();
  Tab * getActiveTab();
  BGui * parent;
 private:
  std::vector<Tab *> tabs;
  GtkWidget * notebook;
  int nTabs;
  int activeTab;
  
};


#endif //ifndef BGUI_H
