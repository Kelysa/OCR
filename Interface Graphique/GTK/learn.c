# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>

//# include "getsetpix.h"
# include "traitement.h"


//gboolean gdk_pixbuf_get_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue);
//gboolean gdk_pixbuf_set_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue);

void from_color_to_greyscale(GdkPixbuf *image);
void from_color_to_black(GdkPixbuf *image);


int main(int argc, char *argv[])
{
  all(argc, argv);
  
  return EXIT_SUCCESS;
}

void all(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  
  GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(widget), 600, 400);
  g_signal_connect(GTK_WINDOW(widget), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *myBox = gtk_vbox_new(0,0);

  GtkWidget *header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  GtkWidget *image; 
  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);

  if(argc > 1)
    {
      image = gtk_image_new_from_file(argv[1]);
      gtk_window_set_title(GTK_WINDOW(widget),argv[1]);
      
      GdkPixbuf *img = gdk_pixbuf_new_from_file(argv[1], NULL);
      
      from_color_to_black(img);

      image = gtk_image_new_from_pixbuf(img);
      
    }


  
  gtk_container_add(GTK_CONTAINER(myBox), header);
  gtk_container_add(GTK_CONTAINER(myBox), image);
  gtk_container_add(GTK_CONTAINER(myBox), footer);

  gtk_container_add(GTK_CONTAINER(widget), myBox);
  
  gtk_widget_show_all(widget);
  gtk_main();

}

void entry_user(GtkWidget *window)
{
  GtkWidget *TBox = gtk_entry_new;
  
  
}

