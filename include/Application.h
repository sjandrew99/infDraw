#ifndef B_CVYGUI_H
#define B_CVYGUI_H

#include "bgui.h"
#include "imageManager.h"
#include "Callbacks.h"
#define APPSTATE_DEFAULT  0
#define APPSTATE_DRAW_RECTANGLE  1
#define APPSTATE_DRAW_LINE 2


struct cvgui_point_t
{
 int x; int y;
};

class Application
{
 public:
 Application ();
 
 BGui gui; 
 
 int valid;
 int init(char *);
 static void * do_draw(void * data);
 static gboolean worker_thread_func(Application *);
 gint worker_thread_id;

 int appState;
 void toDefaultState();

 
};



#endif
