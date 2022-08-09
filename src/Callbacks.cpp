#include "bgui.h"

void Callbacks::imageMotionFunc(GtkWidget * w, GdkEventButton * e, gpointer data)
{
 //fprintf(stderr,"MOUSE MOTION: %lf %lf\n",e->x,e->y);
 Tab * tab = (Tab *)data;
 BGui * pgui = tab->parent->parent;
 //pgui->scratchFrame = pgui->vidMgr.frame;
 //TODO - add something for APPSTATE_DEFAULT here
 if (pgui->appState == APPSTATE_DEFAULT)
 {
  //TODO - check for intersections
 }
 else if (pgui->appState == APPSTATE_DRAW_RECTANGLE && pgui->clickedPoints.size() == 1)
 {
  //draw a rectangle between the first point and the current point
  //tab->imgMgr->scratchFrame.copyTo(tab->imgMgr->frame);
  tab->imgMgr->pop();
  Artist::drawRectangle(tab->imgMgr->frame,pgui->clickedPoints[0].x,pgui->clickedPoints[0].y,e->x,e->y);
  pgui->set_image(&(tab->imgMgr->frame));
 }
 else if (pgui->appState == APPSTATE_DRAW_LINE && pgui->clickedPoints.size() == 1)
 {
  //fprintf(stderr,"IMAGEMOTION\n");
  //tab->imgMgr->scratchFrame.copyTo(tab->imgMgr->frame); // copy the scratchFrame to frame
  tab->imgMgr->pop();
  Artist::drawLine(tab->imgMgr->frame,pgui->clickedPoints[0].x,pgui->clickedPoints[0].y,e->x,e->y);
  pgui->set_image(&(tab->imgMgr->frame)); // should only do this call when we're running line selector in a worker thread
 }
 else if (pgui->appState == APPSTATE_DRAW_ARROW_LINE && pgui->clickedPoints.size() == 1)
 {
  //fprintf(stderr,"IMAGEMOTION\n");
  //tab->imgMgr->scratchFrame.copyTo(tab->imgMgr->frame); // copy the scratchFrame to frame
  tab->imgMgr->pop();
  Artist::drawArrowLine(tab->imgMgr->frame,pgui->clickedPoints[0].x,pgui->clickedPoints[0].y,e->x,e->y);
  pgui->set_image(&(tab->imgMgr->frame)); // should only do this call when we're running line selector in a worker thread
 } 
}


void Callbacks::imageClickFunc(GtkWidget * w, GdkEventButton * e, gpointer data)
{
 if (e->button == GDK_BUTTON_SECONDARY)
 {
  Callbacks::imageRightClickFunc(e,data);
  return;
 }
 
 Tab * tab = (Tab *)data;
 BGui * gui = tab->parent->parent;
 if (gui->appState==APPSTATE_DEFAULT)
 {
  int clicked = 0;
  for (auto i = tab->drawables.begin(); i != tab->drawables.end(); ++i)
  {
   for (auto j= (*i)->clickablePoints.begin(); j != (*i)->clickablePoints.end(); ++j)
   {
    if ( (abs(e->x - j->x) < 5)
         &&
         (abs(e->y - j->y) < 5)
         )
    {
      //(*i)->select();// = ! (*i)->selected;
      (*i)->toggleSelection();
      clicked=1;
      break;
    }
   }
   if (clicked) break; 
  }
 }
 else
 {
  gui->clickedPoints.push_back({e->x, e->y});
 }
}

void Callbacks::imageRightClickFunc(GdkEventButton * e, gpointer data)
{
 //fprintf(stderr,"HERE\n");
 Tab * tab = (Tab *)data;
 BGui * gui = tab->parent->parent;
 if (gui->appState==APPSTATE_DEFAULT)
 {
  int clicked = 0;
  for (auto i = tab->drawables.begin(); i != tab->drawables.end(); ++i)
  {
   for (auto j= (*i)->clickablePoints.begin(); j != (*i)->clickablePoints.end(); ++j)
   {
    if ( (abs(e->x - j->x) < 5)
         &&
         (abs(e->y - j->y) < 5)
         )
    {
      //(*i)->select();// = ! (*i)->selected;
      //(*i)->toggleSelection();
      (*i)->propEditMenu();
      clicked=1;
      break;
    }
   }
   if (clicked) break; 
  }
 }
}

void Callbacks::objectListRightClickFunc(GdkEventButton * e, gpointer data)
{
    Drawable * d = (Drawable *)data;
    d->propEditMenu();
}

//gboolean Callbacks::key_event(GtkWidget * widget, GdkEventKey *event)
void Callbacks::key_event(GtkWidget * w, GdkEventKey * e, gpointer data)
{
 //
 BGui * b = (BGui *)data;
 char * key = gdk_keyval_name(e->keyval); 
 //fprintf(stderr,"pressed: '%s'\n",key);
 //if (gdk_keyval_name(e->keyval) == "l")
 if (strcmp(key,"l") == 0)
 {
  b->setStatusMsg("LINE");
  b->clickedPoints.clear(); 
  b->appState = APPSTATE_DRAW_LINE;
 }
 else if (strcmp(key,"s") == 0)
 {
  b->setStatusMsg("SELECT"); 
  b->clickedPoints.clear();
  b->appState = APPSTATE_DEFAULT;
 }
 else if (strcmp(key,"b") == 0)
 {
  b->setStatusMsg("BOX"); 
  b->clickedPoints.clear();
  b->appState = APPSTATE_DRAW_RECTANGLE;
 }
 else if (strcmp(key,"a") == 0)
 {
  b->setStatusMsg("ARROW"); 
  b->clickedPoints.clear();
  b->appState = APPSTATE_DRAW_ARROW_LINE;
 }
 else if (strcmp(key,"Delete") == 0 && b->appState == APPSTATE_DEFAULT)
 {
  b->notebook->getActiveTab()->deleteSelectedDrawables();
 }
 /*else if (strcmp(key,"t") == 0 && b->appState == APPSTATE_DEFAULT)
 {
  
 }*/

 
 /*else if (strcmp(key,"c") == 0) 
 {
  b->notebook->getActiveTab()->imgMgr->clearFrame();
 }*/
 //return FALSE;
 else
 {
    //print out all hotkey options
    printf("available hotkeys:\n");
    printf("    l : draw line\n");
    printf("    s : select objects\n");
    printf("    b : draw box\n");
    printf("    a : draw arrow\n");
    printf("  del : delete selected objects\n");
 }
}

//called when user clicks a name in the objectList
void Callbacks::select_drawable( GtkWidget * w, GdkEventButton * e, gpointer data)
{
  if (e->button == GDK_BUTTON_SECONDARY)
  {
   Callbacks::objectListRightClickFunc(e,data);
   return;
  }
  
  Drawable * d = (Drawable *)data;
  switch (d->type)
  {
   case DRAWABLE_LINE:
   {
    DLine * l = (DLine *)d; 
    l->toggleSelection();
    break;
   }
   case DRAWABLE_RECTANGLE:
   {
    DRectangle * r = (DRectangle *)(d); 
    r->toggleSelection();
    break;
   }
  }
  //fprintf(stderr,"HERE: %s\n",d->id.c_str());
}
