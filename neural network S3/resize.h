#ifndef _RESIZE_H_
#define _RESIZE_H_

# include <stdlib.h>
# include <SDL.h>
#include <gtk/gtk.h>




typedef struct matrix matrix;

typedef struct network network;


gboolean get_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue);

gboolean set_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue);


matrix resize_matrix(matrix mat, size_t dstH, size_t dstW);


#endif /* _RESIZE_H_ */