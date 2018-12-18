#include    <app.h>
#include    <mainwindow.h>
#include    <stdint.h>

struct _MainWindow {
    GtkApplicationWindow parent;
    GSettings* settings;
    
    GtkMenuBar* menubar;
    
    /* Main menu items. */
    GtkMenuItem* menu_file;
    GtkMenuItem* menu_edit;
    
    /* File menu items. */
    GtkMenuItem* menu_new;
    GtkMenuItem* menu_open;
    GtkMenuItem* menu_folder;
    GtkMenuItem* menu_reload;
    GtkMenuItem* menu_save;
    GtkMenuItem* menu_save_as;
    GtkMenuItem* menu_save_copy;
    GtkMenuItem* menu_save_all;
    GtkMenuItem* menu_rename;
    GtkMenuItem* menu_close;
    GtkMenuItem* menu_close_all;
    GtkMenuItem* menu_close_except;
    GtkMenuItem* menu_load_session;
    GtkMenuItem* menu_save_session;
    GtkMenuItem* menu_print;
    GtkMenuItem* menu_recent;
    GtkMenuItem* menu_open_recents;
    GtkMenuItem* menu_empty_recents;
    GtkMenuItem* menu_exit;
    
    /* Edit menu items. */
    GtkMenuItem* menu_undo;
    GtkMenuItem* menu_redo;
    GtkMenuItem* menu_cut;
    GtkMenuItem* menu_copy;
    GtkMenuItem* menu_paste;
    GtkMenuItem* menu_delete;
    GtkMenuItem* menu_select;
    GtkMenuItem* menu_clipboard;
    GtkMenuItem* menu_path;
    GtkMenuItem* menu_filename;
    GtkMenuItem* menu_directory;
    GtkMenuItem* menu_convert;
    GtkMenuItem* menu_upper;
    GtkMenuItem* menu_lower;
    GtkMenuItem* menu_line;
    GtkMenuItem* menu_duplicate;
    GtkMenuItem* menu_del;
    GtkMenuItem* menu_up;
    GtkMenuItem* menu_down;
    GtkMenuItem* menu_end;
    GtkMenuItem* menu_win;
    GtkMenuItem* menu_unix;
    GtkMenuItem* menu_mac;

};

G_DEFINE_TYPE (MainWindow, main_window, GTK_TYPE_APPLICATION_WINDOW)

static void main_window_dispose(GObject* obj) {

    g_print("Main Window Dispose\n");
    
    MainWindow* win = MAIN_WINDOW(obj);
    g_clear_object(&win->settings);
    
    G_OBJECT_CLASS(main_window_parent_class)->dispose(obj);

}

void get_children(GtkWidget* parent, int i) {

    if (GTK_WIDGET_GET_CLASS(parent) == g_type_class_ref(GTK_TYPE_LABEL)) {
        g_print("Found Label: %s\n", gtk_label_get_text(GTK_LABEL(parent)));
    }
    
    g_print("%s\n", gtk_widget_get_name(parent));
    
    if (GTK_IS_BIN(parent) || GTK_IS_MENU_ITEM(parent)) {
    
        GtkWidget* child = gtk_bin_get_child(GTK_BIN(parent));
        get_children(child, i);
    
    }
    
    if (GTK_IS_CONTAINER(parent) || GTK_IS_BOX(parent) || GTK_IS_MENU_SHELL(parent)) {
    
        GList* children = gtk_container_get_children(GTK_CONTAINER(parent));
        
        while ((children = g_list_next(children)) != NULL) {
            get_children(children->data, i);
        }
    
    }

}

static gboolean find_accel (GtkAccelKey* key, GClosure* closure, gpointer data) {
    return data == (gpointer) closure;
}

void set_menu_item_label(GtkMenuItem* menu_item, GtkStyleProvider* provider) {

    if (menu_item == NULL) {
        return;
    }
    
    char accel_label[255] = "";
    const char* menu_label = gtk_menu_item_get_label(menu_item);
    //g_print("%s\n", menu_label);
    
    GtkWidget* label = gtk_bin_get_child(GTK_BIN(menu_item));
    GtkWidget* accel = gtk_accel_label_get_accel_widget(GTK_ACCEL_LABEL(label));
    
    GClosure *closure = NULL;
    GList* list;
    GList *clist = gtk_widget_list_accel_closures (accel);
    
    for (list = clist; list; list = list->next) {
    
        /* we just take the first closure used */
        closure = list->data;
        break;
    
    }
    
    if (closure != NULL) {
    
        GtkAccelGroup* group = gtk_accel_group_from_accel_closure(closure);
        GtkAccelKey* key = gtk_accel_group_find(group, find_accel, closure);
        
        if (key && key->accel_flags & GTK_ACCEL_VISIBLE) {
        
            GdkModifierType mods = key->accel_mods;
            
            if (mods & GDK_CONTROL_MASK) {
            
                if (strlen(accel_label)) {
                    strcat(accel_label, "+");
                }
                
                strcat(accel_label, "Ctrl");
            
            }
            
            if (mods & GDK_SUPER_MASK) {
            
                if (strlen(accel_label)) {
                    strcat(accel_label, "+");
                }
                
                strcat(accel_label, "Siper");
            
            }
            
            if (mods & GDK_MOD1_MASK) {
            
                if (strlen(accel_label)) {
                    strcat(accel_label, "+");
                }
                
                strcat(accel_label, "Alt");
            
            }
            
            if (mods & GDK_SHIFT_MASK) {
            
                if (strlen(accel_label)) {
                    strcat(accel_label, "+");
                }
                
                strcat(accel_label, "Shift");
            
            }
            
            if (strlen(accel_label) > 0) {
                strcat(accel_label, "+");
            }
            
            if (key->accel_key == GDK_KEY_Delete) {
                strcat(accel_label, "Del");
            } else {
                strcat(accel_label, gdk_keyval_name(gdk_keyval_to_upper(key->accel_key)));
            }
        
        }
    
    }
    
    gtk_container_remove(GTK_CONTAINER(menu_item), label);
    
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_container_add(GTK_CONTAINER(menu_item), box);
    
    const char* name = gtk_widget_get_name(GTK_WIDGET(menu_item));
    
    if (strcmp(name, "radio") == 0) {
        label = gtk_radio_button_new_with_mnemonic(NULL, menu_label);
    } else {
        label = gtk_label_new_with_mnemonic(menu_label);
    }
    
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    
    GtkStyleContext* context = gtk_widget_get_style_context(label);
    gtk_style_context_add_class(context, "menu_item_label");
    gtk_style_context_add_provider(context, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    label = gtk_label_new_with_mnemonic(accel_label);
    gtk_box_pack_end(GTK_BOX(box), label, FALSE, FALSE, 3);
    
    context = gtk_widget_get_style_context(label);
    gtk_style_context_add_class(context, "menu_item_accel_label");
    gtk_style_context_add_provider(context, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

}

static void main_window_init(MainWindow* win) {

    g_print("Main Window Initialize\n");
    
    gtk_widget_init_template(GTK_WIDGET(win));
    win->settings = g_settings_new("org.gtk.notepadplusplus");
    
    GtkCssProvider* provider = gtk_css_provider_new();
    //gtk_css_provider_load_from_data(provider, ".menu_item_accel_label { color: alpha(currentColor, 0.55); }", -1, NULL);
    gtk_css_provider_load_from_data(provider, ".menu_item_label { color: green; } .menu_item_accel_label { color: purple; }", -1, NULL);
    
    /* Format and color all file menu items. */
    set_menu_item_label(win->menu_new, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_open, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_folder, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_reload, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_save, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_save_as, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_save_copy, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_save_all, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_rename, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_close, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_close_all, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_close_except, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_load_session, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_save_session, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_print, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_recent, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_open_recents, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_empty_recents, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_exit, GTK_STYLE_PROVIDER(provider));
    
    /* Format and color all edit menu items. */
    set_menu_item_label(win->menu_undo, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_redo, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_cut, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_copy, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_paste, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_delete, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_select, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_clipboard, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_path, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_filename, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_directory, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_convert, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_upper, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_lower, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_line, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_duplicate, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_del, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_up, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_down, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_end, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_win, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_unix, GTK_STYLE_PROVIDER(provider));
    set_menu_item_label(win->menu_mac, GTK_STYLE_PROVIDER(provider));
    
    g_object_unref(provider);
    
    g_object_set(gtk_settings_get_default(), "gtk-shell-shows-app-menu", FALSE, NULL);
    gtk_widget_show_all(GTK_WIDGET(win));
    
    get_children(GTK_WIDGET(win->menu_win), -1);
    
    //GtkWidget* box = gtk_bin_get_child(GTK_BIN(win->menu_win));
    //GtkWidget* button = gtk_bin_get_child(GTK_BIN(box));
    //GList* children = gtk_container_get_children(GTK_CONTAINER(box));
    
    //while ((children = g_list_next(children)) != NULL) {
    //    get_children(children->data, -1);
        //g_print("%s\n", gtk_widget_get_name(button));
    //}
    //gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
    
    /*if (GTK_WIDGET_GET_CLASS(win->menubar) == g_type_class_ref(GTK_TYPE_MENU)) {
        g_print("YAY");
    }*/
    
    //get_children(GTK_WIDGET(win->menubar), -1);

}

static void main_window_class_init(MainWindowClass* class) {

    g_print("Main Window Class Init\n");
    
    G_OBJECT_CLASS(class)->dispose = main_window_dispose;
    gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/org/gtk/notepadplusplus/mainwindow.ui");
    
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menubar);
    
    /* Get our main menu references. */
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_file);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_edit);
    
    /* Get our file menu items references. */
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_new);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_open);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_folder);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_reload);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_save);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_save_as);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_save_copy);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_save_all);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_rename);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_close);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_close_all);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_close_except);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_load_session);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_save_session);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_print);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_recent);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_open_recents);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_empty_recents);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_exit);
    
    /* Get our edit menu items references. */
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_undo);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_redo);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_cut);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_copy);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_paste);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_delete);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_select);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_clipboard);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_path);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_filename);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_directory);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_convert);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_upper);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_lower);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_line);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_duplicate);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_del);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_up);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_down);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_end);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_win);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_unix);
    gtk_widget_class_bind_template_child(GTK_WIDGET_CLASS(class), MainWindow, menu_mac);

}

void main_window_open(MainWindow* win, GFile* file) {
    g_print("Main Window Open");
}

MainWindow* main_window_new(App* app) {
    g_print("Main Window New\n");
    return g_object_new(MAIN_WINDOW_TYPE, "application", app, NULL);
}