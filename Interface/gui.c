# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>
# include <string.h>

#include "gui.h"

char *Opening(GtkWidget *window)
{
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  char *filename;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(window), action,
					"Cancel", GTK_RESPONSE_CANCEL,
					"Open", GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
    }

  gtk_widget_destroy (dialog);
  return filename;
}

 
GtkWidget *Header()//GtkWidget *window)
{
  GtkWidget *res = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  
  GtkWidget *start = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(start), "Start");
  GtkWidget *path = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(path), "File");
  GtkWidget *perct = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(perct), 3);
  gtk_entry_set_width_chars(GTK_ENTRY(perct), 3);
  
  GtkWidget *perctText = gtk_label_new("%     ");
  
  
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
  g_signal_connect(GTK_WINDOW(widget), "destroy", G_CALLBACK(gtk_main_quit),
		   NULL);

  GtkWidget *myBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);

  GtkWidget *header = Header(widget);
  gtk_box_set_homogeneous (GTK_BOX(header), TRUE);
  GtkWidget *image; 
  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);

  char *path = Opening(widget);

  image = gtk_image_new_from_file(path);
  gtk_window_set_title(GTK_WINDOW(widget),path);
      



  
  gtk_container_add(GTK_CONTAINER(myBox), header);
  gtk_container_add(GTK_CONTAINER(myBox), image);
  gtk_container_add(GTK_CONTAINER(myBox), footer);

  gtk_box_set_center_widget(GTK_BOX(myBox), header);

  gtk_container_add(GTK_CONTAINER(widget), myBox);
  
  gtk_widget_show_all(widget);
  gtk_main();

}

int main(int argc, char *argv[])
{
  All(argc, argv);
  
  return EXIT_SUCCESS;
}

