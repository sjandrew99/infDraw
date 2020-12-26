#ifndef BGUI_H
#define BGUI_H
#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <vector>

#include "controlPanel.h"
#include "imageViewPort.h"
#include "imageManager.h"
#include "tabbedNotebook.h"
#include "common.h"

class Application;
class BGui
{
 
 public:
  BGui(Application * parent);
  ~BGui();
  int setup();
  int set_image(cv::Mat * image);
  
  static 
  void on_window_closed(GtkWidget * window, gpointer data);
  
  int isClosed()
  {
   return closed;
  }
  std::vector <d_point_t> clickedPoints;
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
