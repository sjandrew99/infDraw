#include "Application.h"

void Callbacks::imageMotionFunc(GtkWidget * w, GdkEventButton * e, gpointer data)
{
 //fprintf(stderr,"MOUSE MOTION: %lf %lf\n",e->x,e->y);
 Tab * tab = (Tab *)data;
 Application * pgui = tab->parent->parent->parent;
 //pgui->scratchFrame = pgui->vidMgr.frame;
 if (pgui->appState == APPSTATE_DRAW_RECTANGLE && pgui->gui.clickedPoints.size() == 1)
 {
  //draw a rectangle between the first point and the current point
  tab->imgMgr->scratchFrame.copyTo(tab->imgMgr->frame);
  cv::line(tab->imgMgr->frame, cv::Point(pgui->gui.clickedPoints[0].x,pgui->gui.clickedPoints[0].y), cv::Point(e->x,pgui->gui.clickedPoints[0].y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(pgui->gui.clickedPoints[0].x,pgui->gui.clickedPoints[0].y), cv::Point(pgui->gui.clickedPoints[0].x,e->y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(e->x,e->y), cv::Point(e->x,pgui->gui.clickedPoints[0].y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(e->x,e->y), cv::Point(pgui->gui.clickedPoints[0].x,e->y), cv::Scalar(0,0,0), 2);
  pgui->gui.set_image(0,&(tab->imgMgr->frame));
 }
 else if (pgui->appState == APPSTATE_DRAW_LINE && pgui->gui.clickedPoints.size() == 1)
 {
  //fprintf(stderr,"IMAGEMOTION\n");
  tab->imgMgr->scratchFrame.copyTo(tab->imgMgr->frame); // copy the scratchFrame to frame
  cv::line(tab->imgMgr->frame, cv::Point(pgui->gui.clickedPoints[0].x,pgui->gui.clickedPoints[0].y), cv::Point(e->x,e->y), cv::Scalar(0,0,0), 2);
  pgui->gui.set_image(0,&(tab->imgMgr->frame)); // should only do this call when we're running line selector in a worker thread
 } 
}


void Callbacks::imageClickFunc(GtkWidget * w, GdkEventButton * e, gpointer data)
{
 //fprintf(stderr,"CLICKED: %lf %lf\n", e->x, e->y);
 Tab * tab = (Tab *)data;
 Application * app = tab->parent->parent->parent;
 //fprintf(stderr,"APP = %p\n",app);
 app->gui.clickedPoints.push_back({(int)e->x, (int)e->y});
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
  b->parent->appState = APPSTATE_DRAW_LINE;
 }
 else if (strcmp(key,"s") == 0)
 {
  b->setStatusMsg("SELECT"); 
  b->clickedPoints.clear();
  b->parent->appState = APPSTATE_DEFAULT;
 }
 else if (strcmp(key,"b") == 0)
 {
  b->setStatusMsg("BOX"); 
  b->clickedPoints.clear();
  b->parent->appState = APPSTATE_DRAW_RECTANGLE;
 }
 else if (strcmp(key,"c") == 0) 
 {
  b->notebook->getActiveTab()->imgMgr->clearFrame();
 }
 //return FALSE;
}

/*void Callbacks::toggle_playback(GtkWidget * widget, gpointer data)
{
 VideoManager * vidMgr = (VideoManager *)data;
 vidMgr->togglePlayback();
}*/
