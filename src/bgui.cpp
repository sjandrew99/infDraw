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

void close_dialog(GtkWidget * w, GdkEventButton* e, gpointer data)
{
 gtk_widget_destroy(GTK_WIDGET(data));
}

typedef struct
{
 GtkWidget * dialog;
 GtkWidget * widthEntry;
 GtkWidget * heightEntry;
 Tab * tab;
} resizeCanvasData;

//static 
resizeCanvasData rcData;

void resize_canvas_cb(GtkWidget * window, GdkEventButton*e, gpointer data)
{
 resizeCanvasData * r = (resizeCanvasData *)data;
 int w,h;
 char * str = (char *)malloc(gtk_entry_get_text_length(GTK_ENTRY(r->widthEntry)) + 1);
 /*GtkEntryBuffer * buffer = gtk_entry_get_buffer(GTK_ENTRY(r->widthEntry));
 fprintf(stderr,"bufsize: %d\n",gtk_entry_buffer_get_bytes(buffer));
 if(sscanf(gtk_entry_get_text(GTK_ENTRY((r->widthEntry))), "%s",str) != 1)
 {
  fprintf(stderr,"ERROR: INVALID INPUT\n");
  return;
 }*/
 if(sscanf(gtk_entry_get_text(GTK_ENTRY(r->widthEntry)), "%d",&w) != 1)
 {
  fprintf(stderr,"ERROR: INVALID INPUT\n");
  return;
 }
 if(sscanf(gtk_entry_get_text(GTK_ENTRY(r->heightEntry)), "%d",&h) != 1)
 {
  fprintf(stderr,"ERROR: INVALID INPUT\n");
  return;
 }
 r->tab->imgMgr->resizeFrame(w,h);
 //fprintf(stderr,"%s\n",gtk_entry_get_text(GTK_ENTRY(r->widthEntry)));
 gtk_widget_destroy(r->dialog);
}

void BGui::resizeCanvas(GtkWidget * window, gpointer data)
{
 BGui * g = (BGui *)data;
 Tab * tab = g->notebook->getActiveTab();
 //TODO - pop up a dialog here
 GtkWidget *dialog;
 GtkDialogFlags flags;
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 /*dialog = gtk_dialog_new_with_buttons("Message",GTK_WINDOW(g->window),flags, 
                                      ("_OK"),GTK_RESPONSE_NONE,
                                      ("_CANCEL"),GTK_RESPONSE_NONE,NULL);*/
 dialog = gtk_dialog_new();
 GtkWidget * cBox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
 GtkWidget * grid = gtk_grid_new();
 gtk_box_pack_start(GTK_BOX(cBox),grid,TRUE,TRUE,0);
 //gtk_container_add(GTK_CONTAINER(c),grid);                                      
 GtkWidget * wLabel = gtk_label_new("Width:");
 gtk_grid_attach(GTK_GRID(grid),wLabel,0,0,1,1);
 GtkWidget * widthEntry = gtk_entry_new();
 char label[128]; sprintf(label,"%d",tab->imgMgr->width);
 gtk_entry_set_text(GTK_ENTRY(widthEntry), label);
 gtk_grid_attach(GTK_GRID(grid),widthEntry,1,0,1,1);
 GtkWidget * hLabel = gtk_label_new("Height:");
 
 gtk_grid_attach(GTK_GRID(grid),hLabel,0,1,1,1);
 GtkWidget * heightEntry = gtk_entry_new();
 gtk_grid_attach(GTK_GRID(grid),heightEntry,1,1,1,1);                                      
 sprintf(label,"%d",tab->imgMgr->height);
 gtk_entry_set_text(GTK_ENTRY(heightEntry), label);
 GtkWidget * oButton = gtk_button_new_with_label("Apply");
 
 rcData = {dialog, widthEntry, heightEntry, tab}; //declare it static so it'll persist after this function
 g_signal_connect(oButton,"button-press-event",G_CALLBACK(resize_canvas_cb),&rcData);
 gtk_grid_attach(GTK_GRID(grid),oButton,0,2,1,1);                                      
 GtkWidget * cButton = gtk_button_new_with_label("Cancel");
 g_signal_connect(cButton,"button-press-event",G_CALLBACK(close_dialog),dialog);
 gtk_grid_attach(GTK_GRID(grid),cButton,1,2,1,1);                                      
 //gtk_box_pack_start(GTK_BOX(cBox),widthEntry,TRUE,TRUE,0);
 //gtk_dialog_add_action_widget(GTK_DIALOG(dialog),widthEntry,GTK_RESPONSE_NONE);
 //gtk_grid_attach(GTK_GRID(grid),widthEntry,0,0,1,1);
 gtk_widget_show_all(dialog);
 
 //tab->imgMgr->resizeFrame(0,0);
}

int initMenuBar(BGui * parent, GtkWidget * parentGrid, int col, int row)
{
    GtkWidget * menuBar = gtk_menu_bar_new(); //gtk_widget_show(menuBar);
    gtk_grid_attach(GTK_GRID(parentGrid),menuBar,col,row,1,1);
    
    GtkWidget * fileMenu = gtk_menu_new();
    GtkWidget * fileMi = gtk_menu_item_new_with_label("File");
    GtkWidget * newMi = gtk_menu_item_new_with_label("New");
    GtkWidget * openMi = gtk_menu_item_new_with_label("Open");
    GtkWidget * saveMi = gtk_menu_item_new_with_label("Save");
    GtkWidget * quitMi = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(BGui::on_window_closed), parent);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi),fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),newMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),openMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),saveMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar),fileMi);   
    
    GtkWidget * editMenu = gtk_menu_new(); 
    GtkWidget * editMi = gtk_menu_item_new_with_label("Edit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(editMi),editMenu);
    GtkWidget * resizeMi = gtk_menu_item_new_with_label("Resize Canvas");
    gtk_menu_shell_append(GTK_MENU_SHELL(editMenu),resizeMi);
    g_signal_connect(G_OBJECT(resizeMi),"activate",G_CALLBACK(BGui::resizeCanvas),parent);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar),editMi);   
 return 0;
}