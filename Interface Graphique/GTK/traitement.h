
#include "getsetpix.h"

gboolean gdk_pixbuf_get_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue);
gboolean gdk_pixbuf_set_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue);

void from_color_to_greyscale(GdkPixbuf *image)
{
  size_t height, width;
  height = gdk_pixbuf_get_height(image);
  width = gdk_pixbuf_get_width(image);

  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++)
      {
	guchar red = 0, green = 0, blue = 0;
	gdk_pixbuf_get_colors(image, j, i, &red, &green, &blue);

	//g_print(red);
	guchar grey = 0.21*(double)red + 0.72*(double)green + 0.07*(double)blue;
	gdk_pixbuf_set_colors(image, j, i, grey, grey, grey);
      }
}


void from_color_to_black(GdkPixbuf *image)
{
  size_t height, width;
  height = gdk_pixbuf_get_height(image);
  width = gdk_pixbuf_get_width(image);

  for(size_t i = 0; i < height; i++)
    for(size_t j = 0; j < width; j++)
      {
	guchar red = 0, green = 0, blue = 0;
	
	gdk_pixbuf_get_colors(image, j, i, &red, &green, &blue);
	
	guchar borw = ((0.21*(double)red + 0.72*(double)green + 0.07*(double)blue) > 127) ? 255 : 0;
	gdk_pixbuf_set_colors(image, j, i, borw, borw, borw);
      }
}
