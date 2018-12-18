#include    <app.h>
#include    <libgen.h>

GtkWidget* create_menu_bar() {

    GtkWidget* menu_bar = gtk_menu_bar_new();
    
    GtkWidget* menu = gtk_menu_item_new_with_mnemonic("_File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_Edit");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_Search");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_View");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("En_coding");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_Language");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("Settin_gs");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_Run");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_Window");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    menu = gtk_menu_item_new_with_mnemonic("_?");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    
    return menu_bar;

}

void activate(GtkApplication* app, gpointer user_data) {

    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Notepad++ -");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(box), create_menu_bar());
    
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);

}

int main1(int argc, char* argv[]) {

    GtkApplication* app = gtk_application_new("org.gtk.notepadplusplus", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;

}

int main(int argc, char* argv[]) {

    char* exec = argv[0];
    char* end = "/../lib/notepad++-bin";
    
    size_t len_exec = strlen(exec);
    size_t len_end = strlen(end);
    
    if (len_end <= len_exec && strcmp(exec + len_exec - len_end, end) == 0) {
        g_print("%s\n", exec);
        g_setenv("GSETTINGS_SCHEMA_DIR", dirname(exec), FALSE);
    }
    
    DIR* dir = opendir(exec);
    
    if (dir) {
        closedir(dir);
    }
    
    //g_setenv("GSETTINGS_SCHEMA_DIR", ".", FALSE);
    return g_application_run(G_APPLICATION(app_new()), argc, argv);

}
