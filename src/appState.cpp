#include "bgui.h"

static int currently_drawing = 0;

void rectangleDrawThread(BGui * gui) 
{
 static int drew = 0;
 Tab * tab = gui->notebook->getActiveTab();
 if (gui->clickedPoints.size() == 1 && !drew)
 {
   Artist::drawPoint(tab->imgMgr->frame,gui->clickedPoints[0].x,gui->clickedPoints[0].y);
   tab->imgMgr->cache();
   drew = 1;
   gui->set_image(&(tab->imgMgr->frame));
 } 
 if (gui->clickedPoints.size() == 2)
 {
  //save the rectangle to frame:
  tab->addRectangle(gui->clickedPoints[0].x,gui->clickedPoints[0].y,gui->clickedPoints[1].x,gui->clickedPoints[1].y);
  gui->toDefaultState();
  drew = 0;
 }
}

void lineDrawThread(BGui * gui) 
{
 //fprintf(stderr,"line selector thread\n");
 static int drew = 0;
 Tab * tab = gui->notebook->getActiveTab();
 if (gui->clickedPoints.size() == 1 && !drew)
 {
   Artist::drawPoint(tab->imgMgr->frame,gui->clickedPoints[0].x,gui->clickedPoints[0].y);
   tab->imgMgr->cache();
   drew = 1;
   gui->set_image(&(tab->imgMgr->frame)); 
 }
 if (gui->clickedPoints.size() == 2)
 {
  tab->addLine(gui->clickedPoints[0].x,gui->clickedPoints[0].y,gui->clickedPoints[1].x,gui->clickedPoints[1].y);
  gui->toDefaultState();
  drew = 0;
 }
}

void drawThread(BGui * gui)
{
      //fprintf(stderr,"HERE\n");
      Tab * tab = gui->notebook->getActiveTab();
      tab->clear();
      tab->drawAll();
      gui->set_image(&(tab->imgMgr->frame));
}

//do_draw will be executed in a separate thread whenever we would like to update our animation
void * BGui::do_draw(void * ptr)
{
    BGui * gui = (BGui *)ptr;
    currently_drawing = 1;
    switch (gui->appState)
    {
     case APPSTATE_DEFAULT:
      drawThread(gui);
      break;
     case APPSTATE_DRAW_LINE:
      lineDrawThread(gui);
      break;
     case APPSTATE_DRAW_RECTANGLE:
      rectangleDrawThread(gui);
      break;
    }
    currently_drawing = 0;
    return NULL;
}

void BGui::toDefaultState()
{
  clickedPoints.clear();
  appState = APPSTATE_DEFAULT;
  setStatusMsg("SELECT"); 
}

