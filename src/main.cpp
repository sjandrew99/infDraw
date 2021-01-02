#include "bgui.h"

int main(int argc, char **argv)
{
 gtk_init(&argc,&argv);
 
 BGui gui;
 gui.setup(); 

 //for (unsigned int i = 0; i<100; i++)
 // app.gui.notebook->getActiveTab()->addLine(0,0,10,10);

 //int count = 0;
 while(! gui.isClosed() )
 {
  gtk_main_iteration_do(TRUE); //not sure if this should be true or false
  BGui::do_draw(&gui);
  /*count ++;
  if (count < 100)
  {
   if (count % 2 == 0)
    app.gui.notebook->getActiveTab()->addLine(count*3,count*2,count+1,count*5);
   else
    app.gui.notebook->getActiveTab()->addRectangle(count + 4, count *5, count *10, count);
  }*/
 }
}



