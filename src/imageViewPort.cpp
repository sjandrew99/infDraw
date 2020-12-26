#include "imageViewPort.h"


ImageViewPort::ImageViewPort(char * name, GtkWidget * parent_grid,int col, int row,
           GCallback clickedCallback, GCallback mouseMotionCallback, void * callback_data)
{
  image = NULL; //TODO - add an imageManager
  
  frame = gtk_frame_new(NULL); gtk_widget_show(frame);
  gtk_widget_set_name(frame,name);
  gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_IN);
  gtk_grid_attach(GTK_GRID(parent_grid), frame,col, row, 1, 1);
  
  drawing_area = gtk_drawing_area_new(); gtk_widget_show(drawing_area);
  //TODO - name
  gtk_container_add(GTK_CONTAINER(frame),drawing_area);
  if (clickedCallback != NULL)
  {
   g_signal_connect(drawing_area,"button-press-event",clickedCallback,callback_data);
   gtk_widget_set_events(drawing_area,gtk_widget_get_events(drawing_area) | GDK_BUTTON_PRESS_MASK);
  }
  if (mouseMotionCallback != NULL)
  {
   g_signal_connect(drawing_area,"motion-notify-event",mouseMotionCallback,callback_data);
   gtk_widget_set_events(drawing_area,gtk_widget_get_events(drawing_area) | GDK_POINTER_MOTION_MASK);
  }
   
  g_signal_connect(drawing_area,"draw",G_CALLBACK(ImageViewPort::image_draw),this);
    
}           


//"callback" - called when draw signal emitted
gboolean ImageViewPort::image_draw(GtkWidget* widget, cairo_t *cr, gpointer data) //from cvImageWidget_draw, window_gtk.cpp:914
{
 //fprintf(stderr,"HERERE IN DRAW\n");
 //passed-in widget is the drawing_area, i think
 GdkPixbuf * pixbuf = NULL;
 //gui_t * gui = (gui_t*)data;
 //gui_int_pair_t * gui_int_pair = (gui_int_pair_t *)data;
 //BGui * gui = gui_int_pair->gui;
 //int imageNumber = gui_int_pair->n;
 ImageViewPort * imvp = (ImageViewPort *)data;
/* fprintf(stderr,"(a) %d %d %d \n(b) %d %d %d\n(c) %d %d %d\n",gui->image->data[0],gui->image->data[1],gui->image->data[2],
  gui->image->data[3],gui->image->data[4],gui->image->data[5],
  gui->image->data[6],gui->image->data[7],gui->image->data[8]);*/
//  fprintf(stderr,"(1) HERE IN DRAW\n");

 if (imvp->image != NULL)
 {
  //fprintf(stderr,"(2) HERE IN DRAW - %d x %d\n",imvp->image->rows,imvp->image->cols);
  pixbuf = gdk_pixbuf_new_from_data(imvp->image->data, 
                                    GDK_COLORSPACE_RGB, 
                                    false,
                                    8, 
                                    MIN(imvp->image->cols, gtk_widget_get_allocated_width(widget)),
                                    MIN(imvp->image->rows, gtk_widget_get_allocated_height(widget)),
                                    imvp->image->cols * 3,
                                    //gui->image->step, 
                                    NULL, 
                                    NULL);
   gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
   cairo_paint(cr);
 }
 
 if(pixbuf)
    g_object_unref(pixbuf);

 return TRUE;
}
