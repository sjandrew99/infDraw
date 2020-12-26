#include "bgui.h"

ControlPanel::ControlPanel(GtkWidget * parentGrid, int col, int row, int height, int width)
{
     panel = gtk_frame_new(NULL);
     
     //sprintf(name,"Control panel"); gtk_widget_set_name(controlPanel,name);
     gtk_frame_set_shadow_type(GTK_FRAME(panel),GTK_SHADOW_IN);
     //gtk_grid_attach(GTK_GRID(parentGrid), panel, row,col, width, height);
     gtk_grid_attach(GTK_GRID(parentGrid), panel, col,row, height,width);
     gtk_widget_show(panel);

     grid = gtk_grid_new();
     gtk_grid_set_column_spacing(GTK_GRID(grid),10);
     gtk_container_add(GTK_CONTAINER(panel),grid);
     gtk_widget_show(grid);     
}

ControlPanel::~ControlPanel()
{
 for (unsigned int i = 0; i<controls.size(); i++)
 {
  gtk_widget_destroy(this->controls[i]);
 }
 this->controls.clear();
 gtk_widget_destroy(this->grid);
 gtk_widget_destroy(this->panel);
}

GtkWidget * ControlPanel::addControl(int type, std::string label, int row, int column)
{
     GtkWidget * control;
     
     if (type == CONTROL_PANEL_BUTTON)
     {
      control = gtk_button_new_with_label(label.c_str());
     }
     else if (type == CONTROL_PANEL_LABEL)
     {
      control = gtk_label_new(label.c_str());
     }
     else if (type == CONTROL_PANEL_COMBO_TEXT)
     {
      control = gtk_combo_box_text_new(); 
      gtk_combo_box_text_prepend_text(GTK_COMBO_BOX_TEXT(control),label.c_str());
      gtk_combo_box_set_active(GTK_COMBO_BOX(control),0);
     }
     else
     {
      fprintf(stderr,"unknown control type: %d\n", type);
      return NULL;  
     }
     gtk_grid_attach(GTK_GRID(grid), control, row, column, 1,1);
     gtk_widget_show(control);
     controls.push_back(control);     
     controlTypes.push_back(type);
     return control;
}
