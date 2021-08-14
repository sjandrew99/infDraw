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
  GtkWidget * objectList;
  
  int set_image(cv::Mat * image);
  TabbedNotebook * parent;
  ImageManager * imgMgr;
  
  //Artist * artist;
  //std::vector<Drawable*> drawables;
  std::list<Drawable*> drawables;
  //std::vector<> clickablePoints
  //std::vector<int> drawableTypes; 
  //int addDrawable(int which);
  int addRectangle(float x1,float y1,float x2, float y2, std::string labelText="aaaa",float textPosX=-1, float textPosY=-1);
  int addLine(float x1,float y1,float x2, float y2,std::string labelText="aaaa",float textPosX=-1, float textPosY=-1);
  int addArrowLine(float x1,float y1,float x2, float y2,float tipLength=.1, std::string labelText="aaaa",float textPosX=-1, float textPosY=-1);
  
  void drawAll();
  void clear();
  void deleteSelectedDrawables();
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
