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

 //for (unsigned int i = 0; i<100; i++)
 // app.gui.notebook->getActiveTab()->addLine(0,0,10,10);

 //int count = 0;
 while(! app.gui.isClosed() )
 {
  gtk_main_iteration_do(TRUE); //not sure if this should be true or false
  /*count ++;
  if (count < 100)
  {
   if (count % 2 == 0)
    app.gui.notebook->getActiveTab()->addLine(count*3,count*2,count+1,count*5);
   else
    app.gui.notebook->getActiveTab()->addRectangle(count + 4, count *5, count *10, count);
  }*/
 }
 //gtk_main();
 gdk_threads_leave();
}



