#ifndef BERN_CALLBACKS_H
#define BERN_CALLBACKS_H

#include "Drawable.h"

namespace Callbacks
{
 //static 
 void addCounter(GtkWidget * widget, gpointer data);
 //static 
 void addDetector(GtkWidget * widget, gpointer data); //gui callback
 //static 
 void toggle_playback(GtkWidget * widget, gpointer data);
 //static 
 void imageClickFunc(GtkWidget * w, GdkEventButton * e, gpointer data);
 void imageRightClickFunc(GdkEventButton * e, gpointer data);

 //static 
 void imageMotionFunc(GtkWidget * w, GdkEventButton * e, gpointer data);

 //gboolean key_event(GtkWidget * w, GdkEventKey *event);
 void key_event(GtkWidget * w, GdkEventKey * e, gpointer data);

 void select_drawable( GtkWidget * w, GdkEventButton * e, gpointer data);

};

#endif
