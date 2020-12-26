#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
//#include <opencv2/opencv.hpp>
#include <gtk/gtk.h>
#include <vector>

#define CONTROL_PANEL_BUTTON 1
#define CONTROL_PANEL_LABEL 2
#define CONTROL_PANEL_COMBO_TEXT 3 //gtk_combo_box_text
#define CONTROL_PANEL_LIST_BOX 4

#define CONTROL_PANEL_TOP 0
#define CONTROL_PANEL_RIGHT 1
#define CONTROL_PANEL_BOTTOM 2
#define CONTROL_PANEL_LEFT 3

class ControlPanel
{
  public:
  
  GtkWidget * panel; //holds controls
  GtkWidget * grid; //holds controls
  std::vector<GtkWidget *> controls;
  std::vector<int> controlTypes;
  
  ControlPanel(GtkWidget * parentGrid, int col, int row, int height, int width); //width, height are in units of rows/columns
  ~ControlPanel();
  GtkWidget *  addControl(int type, std::string label, int row, int column);
};

#endif //ifndef CONTROLPANEL_H
