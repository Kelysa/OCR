# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>
# include <string.h>

//# include "getsetpix.h"
//# include "traitement.h"


//gboolean gdk_pixbuf_get_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue);
//gboolean gdk_pixbuf_set_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue);

//void from_color_to_greyscale(GdkPixbuf *image);
//void from_color_to_black(GdkPixbuf *image);

GtkWidget *SetText(char *text)
{
  GtkTextBuffer *buff = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buff), text, strlen(text));
  GtkWidget *res = gtk_text_view_new_with_buffer(buff);
  
  return res;
}

GtkWidget *Header()
{
  GtkWidget *res = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  
  GtkWidget *start = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(start), "Start");
  GtkWidget *path = gtk_entry_new();
  GtkWidget *perct = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(perct), 3);
  gtk_entry_set_width_chars(GTK_ENTRY(perct), 3);
  
  GtkWidget *perctText = SetText("%");
  
  
  gtk_container_add(GTK_CONTAINER(res), path);
  gtk_container_add(GTK_CONTAINER(res), perct);
  gtk_container_add(GTK_CONTAINER(res), perctText);
  gtk_container_add(GTK_CONTAINER(res), start);

  return res;
  
}

void All(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  
  GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(widget), 600, 400);
  g_signal_connect(GTK_WINDOW(widget), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *myBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);

  GtkWidget *header = Header();
  GtkWidget *image; 
  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);

  if(argc > 1)
    {
      image = gtk_image_new_from_file(argv[1]);
      gtk_window_set_title(GTK_WINDOW(widget),argv[1]);
      
      //GdkPixbuf *img = gdk_pixbuf_new_from_file(argv[1], NULL);
      
      //from_color_to_black(img);

      //image = gtk_image_new_from_pixbuf(img);
      
    }


  
  gtk_container_add(GTK_CONTAINER(myBox), header);
  gtk_container_add(GTK_CONTAINER(myBox), image);
  gtk_container_add(GTK_CONTAINER(myBox), footer);

  gtk_container_add(GTK_CONTAINER(widget), myBox);
  
  gtk_widget_show_all(widget);
  gtk_main();

}




/*
void entry_user(GtkWidget *window)
{
  
  
  
  }*/

int main(int argc, char *argv[])
{
  All(argc, argv);
  
  return EXIT_SUCCESS;
}

