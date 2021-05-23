#include <gtk/gtk.h>
#include "gtk_layout.h"
#include "gtk_css.h"

#include <iostream>

GtkWidget* create_window()
{
    GtkWidget *window;
    GtkBuilder *builder;
    GError* error = NULL;
    GtkCssProvider *cssProvider;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_string(builder, (gchar*)ui_glade, ui_glade_len, &error))
    {
        g_critical("Unable to load file: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "rootWindow"));
    if (!window)
    {
        g_critical("Error getting root window");
    }

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider, (gchar*)ui_css, ui_css_len, &error);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER); //applying css to all widgets

    g_object_unref(builder);
    return window;
}

void add_class_block(GtkBox* classes_box)
{
    GtkWidget *box_new;
    GtkWidget *button_class;
    GtkWidget *button_delete;
    GtkWidget *delete_icon;

    delete_icon = gtk_image_new_from_file("delete_icon.png");

    box_new = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    button_class = gtk_button_new_with_label("Class name here");
    button_delete = gtk_button_new();
    gtk_button_set_image((GtkButton*)button_delete, delete_icon);

    gtk_widget_set_size_request(button_class, 150, -1);
    gtk_widget_set_size_request(button_delete, 50, -1);

    gtk_box_pack_start((GtkBox*)box_new, button_class, true, false, 0);
    gtk_box_pack_end((GtkBox*)box_new, button_delete, true, false, 0);

    gtk_box_pack_end(classes_box, box_new, true, false, 0);

    gtk_widget_show(box_new);
    gtk_widget_show(button_class);
    gtk_widget_show(button_delete);
}

void add_properties_block(GtkBox* properties_box)
{
    GtkWidget *box_new;
    GtkWidget *combobox_new;
    GtkWidget *textview_new;

    box_new = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    combobox_new = gtk_combo_box_text_new();
    gtk_combo_box_text_append((GtkComboBoxText*)combobox_new, "1", "draw: text");
    gtk_combo_box_text_append((GtkComboBoxText*)combobox_new, "1", "draw: fill");
    gtk_combo_box_text_append((GtkComboBoxText*)combobox_new, "1", "draw: line");
    gtk_combo_box_text_append((GtkComboBoxText*)combobox_new, "1", "draw: shield");

    textview_new = gtk_text_view_new();
    gtk_widget_set_size_request(textview_new, -1, 150);

    gtk_box_pack_start((GtkBox*)box_new, combobox_new, true, false, 0);
    gtk_box_pack_end((GtkBox*)box_new, textview_new, true, false, 0);

    gtk_box_pack_end(properties_box, box_new, true, false, 0);

    gtk_widget_show(box_new);
    gtk_widget_show(combobox_new);
    gtk_widget_show(textview_new);
}

GtkWidget *window;

int main(int argc, char *argv[])
{
    std::cout << "GTK+ vesrion: " << gtk_get_major_version() << "." << gtk_get_minor_version() << "." << gtk_get_micro_version() << std::endl;
    gtk_init(&argc, &argv);

    window = create_window();
    gtk_widget_show(window);

    gtk_main();
    return 0;
}

extern "C"
void rootWindow_destroy(GtkWidget *object, gpointer data)
{
    gtk_main_quit();
}

extern "C"
void class_add_button_clicked(GtkButton *button, gpointer data)
{
    add_class_block((GtkBox*)data);
    std::cout << "Class added" << std::endl;
}

extern "C"
void properties_add_button_clicked(GtkWidget *button, gpointer data)
{
    add_properties_block((GtkBox*)data);
    std::cout << "Properties block added" << std::endl;
}

extern "C"
void define_paned_position_limits(GtkWidget *paned)
{
    int window_width, window_height;
    gtk_window_get_size((GtkWindow*)window, &window_width, &window_height);
    if(gtk_paned_get_position((GtkPaned*)paned) < 200)
    {
        gtk_paned_set_position((GtkPaned*)paned, 200);
    }
    if(window_width - gtk_paned_get_position((GtkPaned*)paned) < 400)
    {
        gtk_paned_set_position((GtkPaned*)paned, window_width-400);
    }
}