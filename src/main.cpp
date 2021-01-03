#include "bgui.h"

//#define USE_TIMER
#ifdef USE_TIMER
#include <chrono>
#include <iostream>
#include <ctime>
#endif

int main(int argc, char **argv)
{
 gtk_init(&argc,&argv);
 
 BGui gui;
 gui.setup(); 

 //for (unsigned int i = 0; i<100; i++)
 // app.gui.notebook->getActiveTab()->addLine(0,0,10,10);

 //int count = 0;
 #ifdef USE_TIMER
  double avgTime = 0;
 #endif
 while(! gui.isClosed() )
 {
  gtk_main_iteration_do(TRUE); //not sure if this should be true or false
  #ifdef USE_TIMER
  std::chrono::time_point<std::chrono::system_clock> start,end;
  start = std::chrono::system_clock::now();
  #endif
  BGui::do_draw(&gui);
  #ifdef USE_TIMER
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  avgTime += elapsed_seconds.count();
  //std::cout << "elapsed time: " <<elapsed_seconds.count()*(1.0e6) << " us\n";
  #endif
  /*count ++;
  if (count > 40) break;*/
  /*if (count < 100)
  {
   if (count % 2 == 0)
    app.gui.notebook->getActiveTab()->addLine(count*3,count*2,count+1,count*5);
   else
    app.gui.notebook->getActiveTab()->addRectangle(count + 4, count *5, count *10, count);
  }*/
 }
 #ifdef USE_TIMER
 avgTime /= count;
 std::cout << "avg: " << avgTime*(1.0e6) << "us\n";
 #endif
}



