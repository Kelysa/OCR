# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>


gboolean gdkpixbuf_get_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue) 
{ 
  guchar *pixel=NULL; 
  gint channel=0; 
  gint width=0; 
  
  if (!pixbuf) return FALSE; 
  if (x<0 || y<0) return FALSE; 
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE; 
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE; 
  
  pixel=gdk_pixbuf_get_pixels(pixbuf); 
  channel=gdk_pixbuf_get_n_channels(pixbuf); 
  width=gdk_pixbuf_get_width(pixbuf); 
  
  *red   = pixel[(x*channel)+(y*width*channel)]; 
  *green = pixel[(x*channel)+(y*width*channel)+1]; 
  *blue  = pixel[(x*channel)+(y*width*channel)+2]; 
  
  return TRUE; 
}

gboolean gdkpixbuf_set_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue) 
{ 
  guchar *pixel=NULL; 
  gint channel=0; 
  gint width=0; 
  
  if (!pixbuf) return FALSE; 
  if (x<0 || y<0) return FALSE; 
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE; 
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE; 
  
  pixel=gdk_pixbuf_get_pixels(pixbuf); 
  channel=gdk_pixbuf_get_n_channels(pixbuf); 
  width=gdk_pixbuf_get_width(pixbuf); 
  
  pixel[(x*channel)+(y*width*channel)]   = red; 
  pixel[(x*channel)+(y*width*channel)+1] = green; 
  pixel[(x*channel)+(y*width*channel)+2] = blue; 
  
  return TRUE; 
}


void from_color_to_greyscale(GdkPixbuf *image)
{
  size_t height, width;
  height = gdk_pixbuf_get_height(image);
  width = gdk_pixbuf_get_width(image);

  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++)
      {
	guchar *red = 0, *green = 0, *blue = 0;
	gdkpixbuf_get_colors(image, j, i, red, green, blue);

	//g_print(red);
	//guchar grey = 0.21*(double)red + 0.72*(double)green + 0.07*(double)blue;
	gdkpixbuf_set_colors(image, j, i, *red, *green, 0);
      }
}




int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  
  GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(widget), 600,400);

  GtkWidget *image;

 

  if(argc > 1)
    {
      //printf("Hey\n");
      //printf(argv[1]);
      //printf("\n");
      image = gtk_image_new_from_file(argv[1]);
      gtk_window_set_title(GTK_WINDOW(widget),argv[1]);


      //GError **error = g_error_new();
      GdkPixbuf *image = gdk_pixbuf_new_from_file(argv[1], NULL);
      
      from_color_to_greyscale(image);
      
    }
  
  gtk_container_add(GTK_CONTAINER(widget), image);

  gtk_widget_show_all(widget);
  gtk_main();

  return EXIT_SUCCESS;
}
