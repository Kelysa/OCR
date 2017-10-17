#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

void fenetre(int argc, char *argv[])
{
  GtkWidget *fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  GtkWidget *image;

  if (argc > 1)
    {
      
      image = gtk_image_new_from_file(argv[1]);
    }
     
    /* On ajoute la zone comme conteneur dans la fenêtre */
  gtk_container_add (GTK_CONTAINER (fenetre), image);
 
  gtk_window_set_title(GTK_WINDOW(fenetre), "Hello World");
  gtk_window_set_default_size(GTK_WINDOW(fenetre), 600, 400);
  g_signal_connect(G_OBJECT(fenetre), "delete-event", G_CALLBACK(gtk_main_quit),NULL);
  
  gtk_widget_show(fenetre);

  gtk_main(); 
}

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  fenetre(argc, argv);

  return EXIT_SUCCESS;
}
