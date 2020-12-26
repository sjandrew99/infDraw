#include "Application.h"

static int currently_drawing = 0;

void rectangleDrawThread(Application * app) 
{
 static int drew = 0;
 Tab * tab = app->gui.notebook->getActiveTab();
 if (app->gui.clickedPoints.size() == 1 && !drew)
 {
   Artist::drawPoint(tab->imgMgr->frame,app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y);
   tab->imgMgr->frame.copyTo(tab->imgMgr->scratchFrame);  //scratchFrame now contains the original frame, plus a dot at the clickedPoint
   drew = 1;
   app->gui.set_image(&(tab->imgMgr->frame));
 } 
 if (app->gui.clickedPoints.size() == 2)
 {
  //save the rectangle to frame:
  //tab->addRectangle(app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y,app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y);
  Artist::drawRectangle(tab->imgMgr->frame,app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y,app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y);
  app->toDefaultState();
  tab->addDrawable(DRAWABLE_RECTANGLE);
  drew = 0;
 }
}

void lineDrawThread(Application * app) 
{
 //fprintf(stderr,"line selector thread\n");
 static int drew = 0;
 Tab * tab = app->gui.notebook->getActiveTab();
 if (app->gui.clickedPoints.size() == 1 && !drew)
 {
   Artist::drawPoint(tab->imgMgr->frame,app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y);
   tab->imgMgr->frame.copyTo(tab->imgMgr->scratchFrame);  //scratchFrame now contains the original frame, plus a dot at the clickedPoint
   drew = 1;
   app->gui.set_image(&(tab->imgMgr->frame)); 
 }
 if (app->gui.clickedPoints.size() == 2)
 {
  Artist::drawLine(tab->imgMgr->frame,app->gui.clickedPoints[0].x,app->gui.clickedPoints[0].y,app->gui.clickedPoints[1].x,app->gui.clickedPoints[1].y);
  app->toDefaultState();
  tab->addDrawable(DRAWABLE_LINE);
  drew = 0;
 }
}

void drawThread(Application * app)
{
      Tab * tab = app->gui.notebook->getActiveTab();
      app->gui.set_image(&(tab->imgMgr->frame));
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
      drawThread(app);
      break;
     case APPSTATE_DRAW_LINE:
      lineDrawThread(app);
      break;
     case APPSTATE_DRAW_RECTANGLE:
      rectangleDrawThread(app);
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

void Application::toDefaultState()
{
  gui.clickedPoints.clear();
  appState = APPSTATE_DEFAULT;
  gui.setStatusMsg("SELECT"); 
}

