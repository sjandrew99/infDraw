#include "Application.h"

static int currently_drawing = 0;

void rectangleSelector(Application * app) //TODO - rename this function or something, to make it specific to red blobs
{
 //fprintf(stderr,"RETANGLE SELECTOR\n");
 static int drew = 0;
 Tab * tab = app->gui.notebook->getActiveTab();
 if (app->gui.clickedPoints.size() == 1 && !drew)
 {
   cv::circle(tab->imgMgr->frame,cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y),
              1,cv::Scalar(0,0,0),-1);
   tab->imgMgr->frame.copyTo(tab->imgMgr->scratchFrame);  //scratchFrame now contains the original frame, plus a dot at the clickedPoint
   drew = 1;
   app->gui.set_image(0,&(tab->imgMgr->frame));
 } 
 
 if (app->gui.clickedPoints.size() == 2)
 {
  //save the rectangle to frame:
  cv::line(tab->imgMgr->frame, cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y), cv::Point(app->gui.clickedPoints[1].x,app->gui.clickedPoints[0].y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y), cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[1].y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y), cv::Point(app->gui.clickedPoints[1].x,app->gui.clickedPoints[0].y), cv::Scalar(0,0,0), 2);
  cv::line(tab->imgMgr->frame, cv::Point(app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y), cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[1].y), cv::Scalar(0,0,0), 2);
  
  app->gui.clickedPoints.clear();
  app->appState = APPSTATE_DEFAULT;
  app->gui.setStatusMsg("SELECT"); 
  drew = 0;
 }
}


void line_selector_thing (Application * app) //TODO - replace blocking while loop with multiple calls to this func, then return FALSE when "done"
{
 //fprintf(stderr,"line selector thread\n");
 static int drew = 0;
 Tab * tab = app->gui.notebook->getActiveTab();
 if (app->gui.clickedPoints.size() == 1 && !drew)
 {
   cv::circle(tab->imgMgr->frame,cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y),
              1,cv::Scalar(0,0,0),-1);
   tab->imgMgr->frame.copyTo(tab->imgMgr->scratchFrame);  //scratchFrame now contains the original frame, plus a dot at the clickedPoint
   drew = 1;
   app->gui.set_image(0,&(tab->imgMgr->frame)); 
 }
 if (app->gui.clickedPoints.size() == 2)
 {
  //fprintf(stderr,"HERE\n");
  //save the line to frame:
  cv::line(tab->imgMgr->frame, 
           cv::Point(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y),
           cv::Point(app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y), cv::Scalar(0,0,0), 2);
  
  app->gui.clickedPoints.clear();
  app->appState = APPSTATE_DEFAULT;
  app->gui.setStatusMsg("SELECT"); 
  drew = 0;
 }
}



void playVid(Application * app)
{
      Tab * tab = app->gui.notebook->getActiveTab();
      app->gui.set_image(0,&(tab->imgMgr->frame));
}

//do_draw will be executed in a separate thread whenever we would like to update our animation
void * Application::do_draw(void * ptr)
{
    
    Application * app = (Application *)ptr;
    //app->currently_drawing = 1;
    currently_drawing = 1;
    switch (app->appState)
    {
     case APPSTATE_DEFAULT:
      playVid(app);
      break;
     case APPSTATE_DRAW_LINE:
      line_selector_thing(app);
      break;
     case APPSTATE_DRAW_RECTANGLE:
      rectangleSelector(app);
      break;
    }
    currently_drawing = 0;
    return NULL;
}

gboolean Application::worker_thread_func(Application * app)
{
 //https://developer.gnome.org/gtk-tutorial/stable/c1759.html
 //https://www.cairographics.org/threaded_animation_with_cairo/ 
//TODO - use the signal method on the website, rather than creating a new thread every time
//TODO - use the gtk3 way of doing threads: https://developer.gnome.org/gdk3/stable/gdk3-Threads.html
 static gboolean first_execution = TRUE;
 //int drawing_status = g_atomic_int_get(&(app->currently_drawing)); 
 int drawing_status = g_atomic_int_get(&currently_drawing);
 if (drawing_status == 0)
 {
  static pthread_t thread_info;
  int iret;
  if (first_execution != TRUE)
  {
   pthread_join(thread_info,NULL);
  } 
  iret = pthread_create(&thread_info, NULL, Application::do_draw, app);
 }
 first_execution = FALSE;
 return TRUE;
}


