gboolean gdk_pixbuf_get_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue) 
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

gboolean gdk_pixbuf_set_colors(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue) 
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
