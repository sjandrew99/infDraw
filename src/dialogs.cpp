#include "dialogs.h"


static void close_dialog(GtkWidget * w, GdkEventButton* e, gpointer data)
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
 //char * str = (char *)malloc(gtk_entry_get_text_length(GTK_ENTRY(r->widthEntry)) + 1);
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

void exportImg(GtkWidget * window, gpointer data)
{
 //TODO - make this less shitty
 //TODO - figure out how to save the image after tab->drawAll, but before clearFrame()
 //TODO - opencv interprets the image as BGR color order, but i use RGB internally - gotta convert 
 BGui * g = (BGui *)data;
 Tab * tab = g->notebook->getActiveTab();
 cv::imwrite("stuff.png",tab->imgMgr->frame); 
}

void saveImg(GtkWidget * window, gpointer data)
{
 BGui * g = (BGui *)data;
 Tab * tab = g->notebook->getActiveTab();
 //cv::imwrite("stuff.png",tab->imgMgr->frame); 
 char * fname = "stuff.json"; //TODO - allow user to enter a filename
 FILE * fp = fopen(fname,"w");
 fprintf(fp,"{\n\"drawables\":\n[\n");
 int count = 0;
 for (auto i = tab->drawables.begin(); i!= tab->drawables.end(); ++i,count++)
 {
  (*i)->toJson(fp);
  if (count != tab->drawables.size()-1)
   fprintf(fp,",");
  fprintf(fp,"\n");
 }
 fprintf(fp,"\n]\n}");
 fclose(fp);
}

#include <nlohmann/json.hpp>
using json = nlohmann::json;
void loadImg(GtkWidget * window, gpointer data)
{
 BGui * g = (BGui *)data;
 Tab * tab = g->notebook->getActiveTab();
 //cv::imwrite("stuff.png",tab->imgMgr->frame); 
 char * fname = "stuff.json"; //TODO - allow user to enter a filename
 
 FILE * fp = fopen(fname,"r");
 fseek(fp,0,SEEK_END);
 long int fsize = ftell(fp) + 1;  
 fseek(fp,0,SEEK_SET);
 char * buf = (char *)malloc(sizeof(char*)*fsize);
 fread(buf,1,fsize,fp);
 buf[fsize] = 0;
 auto obj = json::parse(buf);
 free(buf);
 fclose(fp);
 auto drawables = obj["drawables"];
 /*for (int i=0; i<drawables.size(); i++)
 {
      fprintf(stderr,"%s\n",drawables[i]["type"]); 
 }*/
 
 /*for (json::iterator it = obj.begin(); it != obj.end(); ++it)
 {
     std::cout << *it << '\n';
     //std::cout << (*it)["type"] << '\n';
 }*/
 
 for (auto& element : obj)
 {
  //std::cout << element <<'\n';
  //std::cout << element["type"] <<'\n';
  for (auto& drawable : element)
  {
   
   //std::cout << drawable["type"] <<'\n';
   auto dtype = drawable["type"].get<std::string>();
   auto p1 = drawable["p1"].get<std::vector<float>>();
   auto p2 = drawable["p2"].get<std::vector<float>>();
   if (dtype == "LINE")
   {
    tab->addLine(p1[0],p1[1],p2[0],p2[1]);       
   }
   else if (dtype=="RECTANGLE")
   {
    tab->addRectangle(p1[0],p1[1],p2[0],p2[1]);       
   }
   else if (dtype=="ARROWLINE")
   {
   tab->addArrowLine(p1[0],p1[1],p2[0],p2[1]);       
   }
   else
   {
    fprintf(stderr,"Warning - unknown drawable type %s in %s\n",dtype.c_str(),fname);
   }
  } 
 }

}

int initMenuBar(BGui * parent, GtkWidget * parentGrid, int col, int row)
{
    GtkWidget * menuBar = gtk_menu_bar_new(); //gtk_widget_show(menuBar);
    gtk_grid_attach(GTK_GRID(parentGrid),menuBar,col,row,1,1);
    
    GtkWidget * fileMenu = gtk_menu_new();
    GtkWidget * fileMi = gtk_menu_item_new_with_label("File");
    GtkWidget * newMi = gtk_menu_item_new_with_label("New");
    GtkWidget * openMi = gtk_menu_item_new_with_label("Open");
    g_signal_connect(openMi,"activate",G_CALLBACK(loadImg),parent);
    GtkWidget * saveMi = gtk_menu_item_new_with_label("Save");
    g_signal_connect(saveMi, "activate",G_CALLBACK(saveImg),parent);
    GtkWidget * exportMi = gtk_menu_item_new_with_label("Export");
    g_signal_connect(saveMi, "activate",G_CALLBACK(exportImg),parent);
    GtkWidget * quitMi = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(BGui::on_window_closed), parent);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi),fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),newMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),openMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),saveMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),exportMi);
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