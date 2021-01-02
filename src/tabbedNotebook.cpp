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


    //char name[128];
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

int Tab::addRectangle(float x1,float y1,float x2, float y2)
{
 static int nRects = 0;
 Artist::drawRectangle(imgMgr->frame,x1,y1,x2,y2);
 char label[128]; sprintf(label,"Rectangle%d",nRects); nRects++;
 DRectangle * rect = new DRectangle(this,label,x1,y1,x2,y2);
 //fprintf(stderr,"HERE\n");
 GtkWidget * w = gtk_label_new(label); gtk_widget_show(w);
 GtkWidget * e = gtk_event_box_new();
 gtk_container_add(GTK_CONTAINER(e),w); gtk_widget_show(e);
 g_signal_connect(e,"button-press-event",G_CALLBACK(Callbacks::select_drawable),rect);

 //gtk_list_box_insert(GTK_LIST_BOX(objectList),w,-1);
 gtk_list_box_insert(GTK_LIST_BOX(objectList),e,-1);
 drawables.push_back((Drawable *)rect);
 //imgMgr->resizeFrame(2080,1000);
 return 0;
}

int Tab::addLine(float x1,float y1,float x2, float y2)
{
 static int nLines = 0;
 Artist::drawLine(imgMgr->frame,x1,y1,x2,y2);
 char label[128]; sprintf(label,"Line%d",nLines); nLines++;
 DLine * line = new DLine(this,label,x1,y1,x2,y2);
 
 GtkWidget * w = gtk_label_new(label); gtk_widget_show(w);
 GtkWidget * e = gtk_event_box_new();
 gtk_container_add(GTK_CONTAINER(e),w); gtk_widget_show(e);
 g_signal_connect(e,"button-press-event",G_CALLBACK(Callbacks::select_drawable),line);//G_CALLBACK(on_window_closed),this);
 gtk_list_box_insert(GTK_LIST_BOX(objectList),e,-1);
 drawables.push_back((Drawable *)line);
 return 0;
}

void Tab::drawAll()
{
 /*for (int i=0; i<drawables.size(); i++)
 {
  drawables[i]->draw();
 }*/
 for (auto i=drawables.begin(); i!=drawables.end(); i++)
 {
  (*i)->draw();
 }
}

void Tab::clear()
{
 imgMgr->clearFrame();
}

bool is_selected(const Drawable * d) { return d->selected;}

void Tab::deleteSelectedDrawables()
{
 /*for (int i=0; i < drawables.size(); ++i)
 {
  if (drawables[i]->selected)
  {
   delete(drawables[i]);
   removes.push_back(i);
  }
 }*/
 //drawables.remove_if(is_selected);
 //fprintf(stderr,"HERE\n");
 auto i = drawables.begin();
 while(i!= drawables.end())
 {
  if ((*i)->selected)
  {
   i = drawables.erase(i);
   //fprintf(stderr,"DELETE\n");
   //TODO - delete the thing in objectList also, and probably the underlying object
  }
  else
  {
   ++i;
  }
 }
  
 /*for (auto i=drawables.begin(); i!=drawables.end(); i++)
 {
  
 }*/
}