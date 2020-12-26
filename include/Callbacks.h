#ifndef BERN_CALLBACKS_H
#define BERN_CALLBACKS_H

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
 //static 
 void imageMotionFunc(GtkWidget * w, GdkEventButton * e, gpointer data);

 //gboolean key_event(GtkWidget * w, GdkEventKey *event);
 void key_event(GtkWidget * w, GdkEventKey * e, gpointer data);
};

#endif
