#include "bgui.h"
#include "Callbacks.h"
//static int gtk_initialized = 0;
int initMenuBar(BGui * parent, GtkWidget * parentGrid, int col, int row);
BGui::BGui()
{
 this->window = NULL;
 this->winsize = NULL;
 this->notebook = NULL;
 this->closed = -1;
}

BGui::~BGui()
{

}

int BGui::setup()
{    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_container_set_border_width(GTK_CONTAINER(window),4);
    gtk_window_set_title(GTK_WINDOW(window),"infDraw");
    g_signal_connect(window,"key-release-event",G_CALLBACK(Callbacks::key_event),this);
    
    
    winGrid = gtk_grid_new(); gtk_container_add(GTK_CONTAINER(window),winGrid);
    
    //MENU (http://zetcode.com/gui/gtk2/menusandtoolbars/):
    initMenuBar(this,winGrid,0,0);
       
    notebook = new TabbedNotebook(this,winGrid,0,1);
    notebook->addTab();
    
    g_signal_connect(window,"destroy",G_CALLBACK(on_window_closed),this);
    this->statusMsg = gtk_label_new("SELECT"); //gtk_widget_show(this->statusMsg);
    gtk_grid_attach(GTK_GRID(winGrid),statusMsg,0,2,1,1);
    closed = 0;

    gtk_widget_show_all(window);
    appState = APPSTATE_DEFAULT;

    return 0;
}

ControlPanel * Tab::controlPanelLookup(int which)
{
 if (which == CONTROL_PANEL_TOP)
  return controlPanelTop;
 else if (which == CONTROL_PANEL_RIGHT)
  return controlPanelRight;
 else if (which == CONTROL_PANEL_BOTTOM)
  return controlPanelBottom;
 else if (which == CONTROL_PANEL_LEFT)
  return controlPanelLeft;
 else
  return NULL;
}



int BGui::set_image(cv::Mat * image)
{
 notebook->getActiveTab()->set_image(image);
 return 0;
}

void
BGui::on_window_closed(GtkWidget * window, gpointer data)
{
 BGui * g = (BGui *)data;
 g->closed = 1; 
}



GtkWidget * BGui::getChildById(std::string id)
{
 //fprintf(stderr,"HERE IN GET CHILD: %s\n",id.c_str());
 GtkWidget * w = NULL;
 for (unsigned int i=0; i<children.size(); i++)
 {
  //fprintf(stderr,"CHILDIDS[%d} = %s\n",i,childIds[i].c_str());
  if (childIds[i] == id)
  {
   //fprintf(stderr,"CHILDIDS[%d} = %s == %s\n",i,childIds[i].c_str(),id.c_str());
   w = children[i];
   break;
  }
 }
 return w;
}


void BGui::setStatusMsg(std::string m)
{
 gtk_label_set_text(GTK_LABEL(statusMsg), m.c_str());
 //printf("HERE\n");
}

