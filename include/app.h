#ifndef     __APP_H__
#define     __APP_H__

#include    <gtk/gtk.h>

#define     APP_TYPE            (app_get_type())
G_DECLARE_FINAL_TYPE(App, app, NOTEPADPLUSPLUS, APP, GtkApplication)

App* app_new(void);

#endif      // __APP_H__