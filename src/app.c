#include    <app.h>
#include    <mainwindow.h>

struct _App {
    GtkApplication parent;
};

G_DEFINE_TYPE(App, app, GTK_TYPE_APPLICATION);

static void preferences_activated(GSimpleAction* action, GVariant* param, gpointer app) {
    g_print("Preferences Activated\n");
}

static void quit_activated(GSimpleAction* action, GVariant* param, gpointer app) {
    g_print("Quit Activated\n");
    g_application_quit(G_APPLICATION(app));
}

static GActionEntry app_entries[] = {
    { "preferences", preferences_activated, NULL, NULL, NULL },
    { "quit", quit_activated, NULL, NULL, NULL }
};

static void app_open(GApplication* app, GFile** files, gint n_files, const gchar* hint) {
    g_print("App Open\n");
}

static void app_activate(GApplication* app) {

    g_print("App Activate\n");
    
    MainWindow* win = main_window_new(NOTEPADPLUSPLUS_APP(app));
    gtk_window_present(GTK_WINDOW(win));

}

static void app_startup(GApplication* app) {

    g_print("App Startup\n");
    
    const gchar* quit_accels[2] = { "<Ctrl>Q", NULL };
    
    G_APPLICATION_CLASS(app_parent_class)->startup(app);
    
    g_action_map_add_action_entries(G_ACTION_MAP(app), app_entries, G_N_ELEMENTS(app_entries), app);
    gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.quit", quit_accels);
    
    GtkBuilder* builder = gtk_builder_new_from_resource("/org/gtk/notepadplusplus/app-menu.ui");
    GMenuModel* app_menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appmenu"));
    gtk_application_set_app_menu(GTK_APPLICATION(app), app_menu);
    g_object_unref(builder);

}

static void app_init(App* app) {
    g_print("App Init\n");
}

static void app_class_init(AppClass* class) {

    g_print("App Class Init\n");
    
    G_APPLICATION_CLASS(class)->activate = app_activate;
    G_APPLICATION_CLASS(class)->open = app_open;
    G_APPLICATION_CLASS(class)->startup = app_startup;

}

App* app_new(void) {
    g_print("App Created\n");
    return g_object_new(APP_TYPE, "application-id", "org.gtk.notepadplusplus", "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}