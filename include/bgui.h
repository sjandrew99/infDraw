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
#include "Callbacks.h"
#define APPSTATE_DEFAULT  0
#define APPSTATE_DRAW_RECTANGLE  1
#define APPSTATE_DRAW_LINE 2
#define APPSTATE_DRAW_ARROW_LINE 3
class BGui
{
 
 public:
  BGui();
  ~BGui();
  int setup();
  int set_image(cv::Mat * image);
  int appState;
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
  
  static void * do_draw(void * data);

  void setStatusMsg(std::string);
  TabbedNotebook * notebook;
  void toDefaultState();

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
