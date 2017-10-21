#include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <stdlib.h>
# include <stdio.h>
# include <err.h>
void call_black_and_white_fonction()
{
    printf("coucou \n ");
}

int main(int argc,char **argv)
{
    GtkWidget* p_Window;
    GtkWidget* p_Label;
    GtkWidget* button;
    GtkWidget* button2;

    gtk_init(&argc,&argv);
    p_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_Window), "OCR EPITA");
    gtk_window_set_default_size(GTK_WINDOW(p_Window), 260, 260);
    gtk_window_set_position (GTK_WINDOW (p_Window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(p_Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   // sUtf8 = g_locale_to_utf8("tst.jpg", -1, NULL, NULL, NULL);
    button = gtk_button_new_with_label("BLack and white");
    button2 = gtk_button_new_with_label("Coucou");
    
    gtk_container_add(GTK_CONTAINER(p_Window), button);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(call_black_and_white_fonction), NULL);
    
  //  p_Label=gtk_label_new(sUtf8);
  //  g_free(sUtf8);
    gtk_widget_show_all(p_Window);

    gtk_main();

    return EXIT_SUCCESS;
}

// pour compiler faire : gcc $(pkg-config --cflags gtk+-2.0) -c main.c
// puis :  gcc  main.o $(pkg-config --libs gtk+-2.0) -o main
