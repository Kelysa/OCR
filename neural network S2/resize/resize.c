#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

struct matrix {
  size_t h, w;
  double **tab;
};

gboolean get_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint rowstride=0;
  
  if (!pixbuf) return FALSE;
  if (x<0 || y<0) return FALSE;
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE;
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE;
  
  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  rowstride=gdk_pixbuf_get_rowstride(pixbuf);
  
  *red   = pixel[(x*channel)+(y*rowstride)];
  *green = pixel[(x*channel)+(y*rowstride)+1];
  *blue  = pixel[(x*channel)+(y*rowstride)+2];
  
  return TRUE;
}

gboolean set_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar red, guchar green, guchar blue)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint rowstride=0;
  
  if (!pixbuf) return FALSE;
  if (x<0 || y<0) return FALSE;
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE;
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE;
  
  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  rowstride=gdk_pixbuf_get_rowstride(pixbuf);
  
  pixel[(x*channel)+(y*rowstride)] = red;
  pixel[(x*channel)+(y*rowstride)+1] = green;
  pixel[(x*channel)+(y*rowstride)+2] = blue;
  
  return TRUE;
}

void print_matrix(double **mat, size_t lines, size_t cols)
{
  for(size_t i = 0; i < lines; i++) {
    printf("\n");
    for(size_t j = 0; j < cols; j++) {
      printf("%.f", mat[i][j]);
    }
  }
  printf("\n");

}

struct matrix *resize_matrix(struct matrix *mat, size_t dstH, size_t dstW)
{
  
  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 1, 8, mat->w, mat->h);
  
  for(size_t i = 0; i < mat->h; i++)
    {
      for(size_t j = 0; j < mat->w; j++)
	{
	  if(mat->tab[i][j] == 0)
	    set_colors_by_coordinates(pixbuf, j, i, 0, 0, 0);
	  else
	    set_colors_by_coordinates(pixbuf, j, i, 255, 255, 255);	 
	}
    }
  
  GdkPixbuf *r_pixbuf = gdk_pixbuf_scale_simple(pixbuf, dstW, dstH, GDK_INTERP_NEAREST);
  
  struct matrix *r_mat = malloc(sizeof(struct matrix));
  r_mat->h = dstH;
  r_mat->w = dstW;
  r_mat->tab = malloc(sizeof(double)*mat->h);
  for(size_t i = 0; i < mat->h; i++)
    r_mat->tab[i] = malloc(sizeof(double)*mat->w);    
  
  guchar *r = malloc(sizeof(guchar)),
    *g = malloc(sizeof(guchar)),
    *b = malloc(sizeof(guchar));
  
  for(size_t i = 0; i < r_mat->h; i++)
    for(size_t j = 0; j < r_mat->w; j++)
      {
	get_colors_by_coordinates(r_pixbuf, j, i, r, g, b);
	guchar t = 0.21**r+0.72**g+0.07**b;
	//printf("%d\n", *b);
	if(t != 0)
	  r_mat->tab[i][j] = 1;
	else
	  r_mat->tab[i][j] = 0;
      }

  free(r);
  free(g);
  free(b);
  
  return r_mat;


}

int main()
{
  struct matrix *m = malloc(sizeof(struct matrix));
  m->h = 70;
  m->w = 70;
  m->tab = malloc(sizeof(double)*m->h);
  for(size_t i = 0; i < m->h; i++)
    m->tab[i] = malloc(sizeof(double)*m->w);

  
  for(size_t i = 0, j = 0; (i+1) < m->h && j < m->w; i+=1, j+=1) {
      m->tab[i][j] = 1;
      m->tab[i+1][j] = 1;
      //m->tab[m->w-i][j] = 1;
  }
  

  m->tab[0][5] = 1;

  
  print_matrix(m->tab, m->h, m->w);
  
  struct matrix *m_resize = resize_matrix(m, 45, 40);
  print_matrix(m_resize->tab, m_resize->h, m_resize->w);
}
