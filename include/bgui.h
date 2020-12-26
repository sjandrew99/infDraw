#ifndef BGUI_H
#define BGUI_H
#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <vector>

#include "controlPanel.h"
#include "imageViewPort.h"
#include "imageManager.h"

struct cv_point_t
{
 int x; int y;
};

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

class Application;
class BGui
{
 
 public:
  BGui(Application * parent);
  ~BGui();
  int setup();
  int set_image(int imageNumber, cv::Mat * image);
  
  static 
  void on_window_closed(GtkWidget * window, gpointer data);
  
  int isClosed()
  {
   return closed;
  }
  std::vector <cv_point_t> clickedPoints;
  GtkWidget *  addControl(int whichPanel, int type, std::string label, int row, int column);
  int addChild(GtkWidget * w, std::string s) {children.push_back(w); childIds.push_back(s); return 0;}
  GtkWidget * getChildById(std::string s);
  
  
  void setStatusMsg(std::string);
  Application * parent;
  TabbedNotebook * notebook;
 private:
  
  GtkWidget * window; //the window
  GtkAllocation * winsize;
  GtkWidget * winGrid; //grid for holding all the stuff in the window
  
  ControlPanel * headerBar; //TODO - change this to a GtkMenuBar (or whatever it's called)
  
  GtkWidget * statusMsg;
  std::vector<GtkWidget *> children; //used kinda like userdata in matlab guis
  std::vector<std::string> childIds;
    
  int closed;
};


typedef struct gui_int_pair_s {BGui * gui; int n;} gui_int_pair_t;

#endif //ifndef BGUI_H
