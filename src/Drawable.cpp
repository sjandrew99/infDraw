#include "Drawable.h"
//#include "common.h"

typedef struct
{
 GtkWidget * dialog;
 GtkWidget * textEntry;
 DRectangle * rect;
}rectPropData_t;
rectPropData_t rectPropData;

void rectPropCb(GtkWidget * window, GdkEventButton *e, gpointer data)
{
 rectPropData_t * r = (rectPropData_t *)data;
 r->rect->label->text = gtk_entry_get_text(GTK_ENTRY(r->textEntry));
 gtk_widget_destroy(r->dialog);
}

typedef struct
{
 GtkWidget * dialog;
 GtkWidget * textEntry;
 DArrowLine * arrow;
}arrowPropData_t;
arrowPropData_t arrowPropData;

void arrowPropCb(GtkWidget * window, GdkEventButton *e, gpointer data)
{
 arrowPropData_t * r = (arrowPropData_t *)data;
 r->arrow->label->text = gtk_entry_get_text(GTK_ENTRY(r->textEntry));
 gtk_widget_destroy(r->dialog);
}


static void close_dialog(GtkWidget * w, GdkEventButton* e, gpointer data)
{
 gtk_widget_destroy(GTK_WIDGET(data));
}


void Drawable::toggleSelection()
{
 selected = !selected;
}

/////////// TEXTBOX //////////////

DTextBox::DTextBox(Tab * parent, std::string text,float x, float y)
{
 this->parent = parent;
 this->text = text;
 this->x = x;
 this->y = y;
}

void DTextBox::draw()
{
 Artist::drawText(parent->imgMgr->frame, x,y,text);
}

void DTextBox::select()
{
 
}

void DTextBox::highlight()
{

}

void DTextBox::toJson(FILE * fp)
{
 fprintf(fp,"{\"type\": \"TEXTBOX\", \"id\": \"%s\", \"text\": \"%s\", \"x\": %.3f, \"y\": %.3f}",id.c_str(),text.c_str(),x,y);
}

void DTextBox::propEditMenu()
{

}

/////////// LINE //////////////

DLine::DLine(Tab * parent,std::string id, float x1, float y1, float x2, float y2)
{
 this->parent = parent;
 this->id = id;
 type = DRAWABLE_LINE; 
 p1 = {x1,y1};
 p2 = {x2,y2};
 lineWidth = LINE_WIDTH; //TODO - pass this in
 selected = 0;
 
 
 float _x1 = min(x1,x2);
 float _x2 = max(x1,x2);
 float _y1 = min(y1,y2);
 float _y2 = max(y2,y1); 
 
 slope = (y2-y1) / (x2-x1); 
 intrcpt = y2 - (slope*x2);
 this->label = new DTextBox(parent, id, x1,y1);
 
 //add clickable points:
 for (float i=_x1; i<_x2; i++)
 {
  clickablePoints.push_back({i, slope*i + intrcpt});
 } 
}

void DLine::draw() 
{
 Artist::drawLine(parent->imgMgr->frame,p1.x,p1.y,p2.x,p2.y);
 if (selected)
  highlight();
 label->draw();
}

void DLine::select()
{
 //TODO - set something in the tab to show that this is the selected drawable
 selected = 1;
 //highlight();
}
void DLine::unselect()
{
 selected = 0;
}

void DLine::highlight()
{
 int offset = 4*lineWidth;
 //TODO - precompute
 /*Artist::drawRectangle(parent->imgMgr->frame,
                       p1.x-offset,p1.y-offset,
                       p2.x+offset,p2.y-offset,
                       p2.x+offset,p2.y+offset,
                       p1.x-offset,p1.y+offset,
                       0,0,255,lineWidth);*/
 
 //"rotate" the line so that it has a slope of zero:
 float theta = atan2(p2.y-p1.y,p2.x-p1.x); 
 float x1r = p1.x*cos(-theta) - p1.y*sin(-theta); 
 float y1r = p1.x*sin(-theta) + p1.y*cos(-theta);
 float x2r = p2.x*cos(-theta) - p2.y*sin(-theta); 
 //float y2r = p2.x*sin(-theta) + p2.y*cos(-theta); //same as y1r
 //calculate points on a rectangle surrounding the "rotated" line:
 float x1 = x1r-offset; float y1=y1r-offset; //topleft
 float x2 = x2r+offset; float y2 = y1r+offset; //bottomright
 //traveling clockwise from topleft, the rectangle is: (x1,y1), (x2,y1), (x2, y2), (x1, y2)
 /*Artist::drawRectangle(parent->imgMgr->frame,
                       x1, y1, x2, y1,
                       x2,y2, x1, y2,
                       0,0,255,lineWidth);*/
 //rotate the rectangle by theta:
 float x1p = x1*cos(theta) - y1*sin(theta);
 float y1p = x1*sin(theta) + y1*cos(theta);
 
 float x2p = x2*cos(theta) - y1*sin(theta);
 float y2p = x2*sin(theta) + y1*cos(theta);
 
 float x3p = x2*cos(theta) - y2*sin(theta);
 float y3p = x2*sin(theta) + y2*cos(theta);
 
 float x4p = x1*cos(theta) - y2*sin(theta);
 float y4p = x1*sin(theta) + y2*cos(theta);
 
 Artist::drawRectangle(parent->imgMgr->frame,
                       x1p, y1p, x2p, y2p,
                       x3p,y3p, x4p, y4p,
                       0,0,255,lineWidth);
 
                        
 /*static int printed = 0;
 if (!printed)
 {                       
  fprintf(stderr,"\np1: %.1f %.1f\np2: %.1f %.1f\ntheta: %.1f\n",p1.x,p1.y,p2.x,p2.y,theta*180.0/M_PI);
  fprintf(stderr,"x1r/y1r: %.1f %.1f\n",x1r,y1r);
  fprintf(stderr,"x2r/y2r: %.1f %.1f\n",x2r,y1r);
  fprintf(stderr,"rotated rect:\n%.1f %.1f\n%.1f %.1f\n%.1f %.1f\n%.1f %.1f\n",x1p,y1p,x2p,y2p,x3p,y3p,x4p,y4p);
  printed = 1;
 }*/
}

void DLine::toJson(FILE * fp)
{
 fprintf(fp,"{\"type\": \"LINE\", \"id\": \"%s\", \"p1\": [%.3f, %.3f], \"p2\": [%.3f,%.3f]}",id.c_str(),p1.x,p1.y,p2.x,p2.y);
}

void DLine::propEditMenu()
{

}

/////////// ARROW LINE //////////////

DArrowLine::DArrowLine(Tab * parent,std::string id, float x1, float y1, float x2, float y2)
{
 this->parent = parent;
 this->id = id;
 type = DRAWABLE_ARROW_LINE; 
 p1 = {x1,y1};
 p2 = {x2,y2};
 lineWidth = LINE_WIDTH; //TODO - pass this in
 selected = 0;
 
 
 float _x1 = min(x1,x2);
 float _x2 = max(x1,x2);
 float _y1 = min(y1,y2);
 float _y2 = max(y2,y1); 
 
 slope = (y2-y1) / (x2-x1); 
 intrcpt = y2 - (slope*x2);
 this->label = new DTextBox(parent, id, x1,y1);
 
 //add clickable points:
 for (float i=_x1; i<_x2; i++)
 {
  clickablePoints.push_back({i, slope*i + intrcpt});
 } 
}

void DArrowLine::draw() 
{
 Artist::drawArrowLine(parent->imgMgr->frame,p1.x,p1.y,p2.x,p2.y);
 if (selected)
  highlight();
 label->draw();
}

void DArrowLine::select()
{
 //TODO - set something in the tab to show that this is the selected drawable
 selected = 1;
 //highlight();
}
void DArrowLine::unselect()
{
 selected = 0;
}

void DArrowLine::highlight()
{
 int offset = 4*lineWidth;
 //TODO - precompute
 /*Artist::drawRectangle(parent->imgMgr->frame,
                       p1.x-offset,p1.y-offset,
                       p2.x+offset,p2.y-offset,
                       p2.x+offset,p2.y+offset,
                       p1.x-offset,p1.y+offset,
                       0,0,255,lineWidth);*/
 
 //"rotate" the line so that it has a slope of zero:
 float theta = atan2(p2.y-p1.y,p2.x-p1.x); 
 float x1r = p1.x*cos(-theta) - p1.y*sin(-theta); 
 float y1r = p1.x*sin(-theta) + p1.y*cos(-theta);
 float x2r = p2.x*cos(-theta) - p2.y*sin(-theta); 
 //float y2r = p2.x*sin(-theta) + p2.y*cos(-theta); //same as y1r
 //calculate points on a rectangle surrounding the "rotated" line:
 float x1 = x1r-offset; float y1=y1r-offset; //topleft
 float x2 = x2r+offset; float y2 = y1r+offset; //bottomright
 //traveling clockwise from topleft, the rectangle is: (x1,y1), (x2,y1), (x2, y2), (x1, y2)
 /*Artist::drawRectangle(parent->imgMgr->frame,
                       x1, y1, x2, y1,
                       x2,y2, x1, y2,
                       0,0,255,lineWidth);*/
 //rotate the rectangle by theta:
 float x1p = x1*cos(theta) - y1*sin(theta);
 float y1p = x1*sin(theta) + y1*cos(theta);
 
 float x2p = x2*cos(theta) - y1*sin(theta);
 float y2p = x2*sin(theta) + y1*cos(theta);
 
 float x3p = x2*cos(theta) - y2*sin(theta);
 float y3p = x2*sin(theta) + y2*cos(theta);
 
 float x4p = x1*cos(theta) - y2*sin(theta);
 float y4p = x1*sin(theta) + y2*cos(theta);
 
 Artist::drawRectangle(parent->imgMgr->frame,
                       x1p, y1p, x2p, y2p,
                       x3p,y3p, x4p, y4p,
                       0,0,255,lineWidth);
 
                        
 /*static int printed = 0;
 if (!printed)
 {                       
  fprintf(stderr,"\np1: %.1f %.1f\np2: %.1f %.1f\ntheta: %.1f\n",p1.x,p1.y,p2.x,p2.y,theta*180.0/M_PI);
  fprintf(stderr,"x1r/y1r: %.1f %.1f\n",x1r,y1r);
  fprintf(stderr,"x2r/y2r: %.1f %.1f\n",x2r,y1r);
  fprintf(stderr,"rotated rect:\n%.1f %.1f\n%.1f %.1f\n%.1f %.1f\n%.1f %.1f\n",x1p,y1p,x2p,y2p,x3p,y3p,x4p,y4p);
  printed = 1;
 }*/
}

void DArrowLine::toJson(FILE * fp)
{
 fprintf(fp,"{\"type\": \"ARROWLINE\", \"id\": \"%s\", \"p1\": [%.3f, %.3f], \"p2\": [%.3f,%.3f]}",id.c_str(),p1.x,p1.y,p2.x,p2.y);
}

void DArrowLine::propEditMenu()
{
/*GtkWidget * menu = gtk_menu_new();
 gtk_menu_popup_at_pointer(GTK_MENU(menu),NULL);*/
 GtkWidget * dialog = gtk_dialog_new();
 GtkWidget * cBox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
 GtkWidget * grid = gtk_grid_new();
 gtk_box_pack_start(GTK_BOX(cBox),grid,TRUE,TRUE,0);
 //properties:
 int row = 0;
 
 GtkWidget * textLabel = gtk_label_new("Text:");
 gtk_grid_attach(GTK_GRID(grid),textLabel,0,row,1,1);
 GtkWidget * textEntry = gtk_entry_new();
 gtk_entry_set_text(GTK_ENTRY(textEntry),label->text.c_str());
 gtk_grid_attach(GTK_GRID(grid),textEntry,1,row,1,1);
 row++;
 
 GtkWidget * oButton = gtk_button_new_with_label("Apply");
 gtk_grid_attach(GTK_GRID(grid),oButton,0,row,1,1);                                      
 GtkWidget * cButton = gtk_button_new_with_label("Cancel");
 g_signal_connect(cButton,"button-press-event",G_CALLBACK(close_dialog),dialog);
 gtk_grid_attach(GTK_GRID(grid),cButton,1,row,1,1);  
 arrowPropData = {dialog,textEntry,this};
 g_signal_connect(oButton,"button-press-event",G_CALLBACK(arrowPropCb),&arrowPropData);

 
 gtk_widget_show_all(dialog);
}


/////////// RECTANGLE //////////////

DRectangle::DRectangle(Tab * parent, std::string id, float x1, float y1, float x2, float y2)
{
 this->parent = parent;
 this->id = id;
 type = DRAWABLE_RECTANGLE; 
 float _x1 = min(x1,x2);
 float _x2 = max(x1,x2);
 float _y1 = min(y1,y2);
 float _y2 = max(y2,y1); 
 tl = {_x1,_y1};
 tr = {_x2,_y1};
 bl = {_x1,_y2};
 br = {_x2,_y2};
 lineWidth = LINE_WIDTH; //TODO - pass this in
 selected = 0;
 this->label = new DTextBox(parent, id, _x1, _y1+lineWidth*7);
 //TODO - add slope/intercept for line connecting br and tl, and the perp
 //fprintf(stderr,"ADD RECT: %f %f %f %f\n",_x1,_y1,_x2,_y2);
 
 //add clickable points (TODO: non-rotated):
 clickablePoints.clear();
 //top and bottom:
 for (float i=_x1-lineWidth; i<_x2+lineWidth; i+=2)
 {
  clickablePoints.push_back({i,_y1});
  clickablePoints.push_back({i,_y2});
 }
 //sides:
 for (float i=_y1-lineWidth; i<_y2+lineWidth; i+=2)
 {
  clickablePoints.push_back({_x1,i});
  clickablePoints.push_back({_x2,i});
 }
}

void DRectangle::draw()
{
 Artist::drawRectangle(parent->imgMgr->frame,tl.x,tl.y,br.x,br.y);
 if (selected)
  highlight();
 label->draw();
}

void DRectangle::select()
{
 //TODO - set something in the tab to show that this is the selected drawable
 selected=1;
 //highlight();
}
void DRectangle::unselect()
{
 selected=0;
}


void DRectangle::highlight()
{
 //fprintf(stderr,"HIGHLIGHT RECT: %f %f %f %f\n",tl.x-2,tl.y-2,br.x+2,);
 parent->imgMgr->cache();
 //TODO - account for rotation
 Artist::drawRectangle(parent->imgMgr->frame, tl.x-(2*lineWidth),tl.y-(2*lineWidth),br.x+(2*lineWidth),br.y+(2*lineWidth),0,0,255,lineWidth); 
}

void DRectangle::toJson(FILE * fp)
{
 fprintf(fp,"{\"type\": \"RECTANGLE\", \"id\": \"%s\", \"p1\": [%.3f, %.3f], \"p2\": [%.3f,%.3f]}",id.c_str(),tl.x,tl.y,br.x,br.y);
}



void DRectangle::propEditMenu()
{
 /*GtkWidget * menu = gtk_menu_new();
 gtk_menu_popup_at_pointer(GTK_MENU(menu),NULL);*/
 GtkWidget * dialog = gtk_dialog_new();
 GtkWidget * cBox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
 GtkWidget * grid = gtk_grid_new();
 gtk_box_pack_start(GTK_BOX(cBox),grid,TRUE,TRUE,0);
 //properties:
 int row = 0;
 
 GtkWidget * textLabel = gtk_label_new("Text:");
 gtk_grid_attach(GTK_GRID(grid),textLabel,0,row,1,1);
 GtkWidget * textEntry = gtk_entry_new();
 gtk_entry_set_text(GTK_ENTRY(textEntry),label->text.c_str());
 gtk_grid_attach(GTK_GRID(grid),textEntry,1,row,1,1);
 row++;
 
 GtkWidget * oButton = gtk_button_new_with_label("Apply");
 gtk_grid_attach(GTK_GRID(grid),oButton,0,row,1,1);                                      
 GtkWidget * cButton = gtk_button_new_with_label("Cancel");
 g_signal_connect(cButton,"button-press-event",G_CALLBACK(close_dialog),dialog);
 gtk_grid_attach(GTK_GRID(grid),cButton,1,row,1,1);  
 rectPropData = {dialog,textEntry,this};
 g_signal_connect(oButton,"button-press-event",G_CALLBACK(rectPropCb),&rectPropData);

 
 gtk_widget_show_all(dialog);
}