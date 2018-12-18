#ifndef     __GBOX_H__
#define     __GBOX_H__

#include    <gtk/gtk.h>
#include    <app.h>

#define     GBOX_TYPE           (gbox_get_type())
G_DECLARE_FINAL_TYPE(GBox, gbox, G, BOX, GtkBox)

GBox* gbox_new(GtkOrientation orientation, int spacing);

#endif      // __GBOX_H__