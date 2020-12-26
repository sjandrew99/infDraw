#include "Application.h"

Application::Application() :
 gui(this)
{
 appState = APPSTATE_DEFAULT;
  
 gui.setup();
 
 this->valid = 1;
 
 worker_thread_id = gdk_threads_add_timeout(10, (GSourceFunc)(Application::worker_thread_func), this); 
}

