#include "Application.h"
//#include "bgui.h"

int main(int argc, char **argv)
{
 gtk_init(&argc,&argv);
 //gtk_init(0,NULL);
 if( ! g_thread_supported() ) //prevents g_thread_init being called multiple times
    g_thread_init( NULL );
 gdk_threads_init();
 gdk_threads_enter();
 
 Application app;   
 if (!app.valid)
  return -1;

 while(! app.gui.isClosed() )
 {
  gtk_main_iteration_do(TRUE); //not sure if this should be true or false
 }
 //gtk_main();
 gdk_threads_leave();
}



