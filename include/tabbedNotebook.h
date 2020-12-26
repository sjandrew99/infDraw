#ifndef TABBED_NOTEBOOK_H_
#define TABBED_NOTEBOOK_H_
#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <vector>

#include "controlPanel.h"
#include "imageViewPort.h"
#include "imageManager.h"
#include "Drawable.h"
#include "Artist.h"
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
  //Artist * artist;
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
