#include "bgui.h"
#include "Callbacks.h"
//GtkWidget * window;

TabbedNotebook::TabbedNotebook(BGui * _parent, GtkWidget * parentGrid, int col, int row)
{
 //tabs = NULL;
 parent = _parent;
 notebook = gtk_notebook_new(); gtk_widget_show(notebook);
 //gtk_container_add(GTK_GRID(parentGrid),notebook);
 gtk_grid_attach(GTK_GRID(parentGrid),notebook,col,row,1,1);
 nTabs = 0;
 activeTab = -1;
}
int TabbedNotebook::addTab()
{

    nTabs++;
    activeTab = nTabs-1;
    Tab * tab = new Tab(this);
    tabs.push_back(tab);
    tab->grid = gtk_grid_new(); gtk_widget_show(tab->grid);


    char name[128];
    //ImageViewPort * imvp = new ImageViewPort("",tab->grid,1,1,imageClickedCallback,imageMouseMotionCallback,this->parent == NULL ? this : this->parent);
    tab->imageViewPort = new ImageViewPort("",tab->grid,1,1,
                                           G_CALLBACK(Callbacks::imageClickFunc),
                                           G_CALLBACK(Callbacks::imageMotionFunc),tab);
    
    tab->controlPanelTop = new ControlPanel(tab->grid,0,0,3,1);
    tab->controlPanelRight = new ControlPanel(tab->grid,2,1,1,1);
    tab->controlPanelBottom = new ControlPanel(tab->grid,0,2,3,1);
    tab->controlPanelLeft = new ControlPanel(tab->grid,0,1,1,1);   

    //tab->statusMsg = 
    //tab->controlPanelTop->addControl(CONTROL_PANEL_LABEL,"stuff",0,0);
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),tab->grid,gtk_label_new("Chart1"));
    
    tab->objectList = tab->controlPanelRight->addControl(CONTROL_PANEL_LIST_BOX,"objects",0,0);
    
    return (nTabs-1);   
}

int Tab::set_image(cv::Mat * image)
{
 //fprintf(stderr,"HERE IN SET %d x %d\n",image->rows,image->cols);
 gtk_widget_set_size_request(imageViewPort->drawing_area,image->cols,image->rows);
 //fprintf(stderr,"HERE IN SET2\n");
 imageViewPort->image = image;
 //fprintf(stderr,"HERE IN SET IMAGE - %d x %d\n",image->rows,image->cols);
 gtk_widget_queue_draw(imageViewPort->drawing_area); //or draw all?
 //gtk_widget_queue_draw(Window); //or draw all?
 return 0;
}

Tab::Tab(TabbedNotebook * _parent)
{
 parent = _parent;
 imgMgr = new ImageManager(1080,920);
}

Tab * TabbedNotebook::getActiveTab()
{
 return tabs[activeTab];
}

int Tab::addDrawable(int which)
{
 switch (which)
 {
  case DRAWABLE_RECTANGLE:
  {
   DRectangle * rect = new DRectangle();
   GtkWidget * w = gtk_label_new("stuff"); gtk_widget_show(w);
   gtk_list_box_insert(GTK_LIST_BOX(objectList),w,-1);
   break; 
  }
  case DRAWABLE_LINE:
  {
   break;
  }
 }
 return 0;
}