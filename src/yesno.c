/*
    Contains the YesNo dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/
#include "yesno.h"

int res = NO;

void set_yes(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy)
{
  res = YES;
  gtk_widget_destroy(toDestroy);
}

void set_no(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy)
{
  res = NO;
  gtk_widget_destroy(toDestroy);
}

short create_yes_no_dialog(int argc, char **argv, int start)
{
  if(argc - (start+3) < 1)
    return -1;

  char *msg = argv[start+1];
  int width  = atoi(argv[start+2]);
  int height = atoi(argv[start+3]);

  //Create stuff
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(width > 0 && height > 0)
    gtk_window_resize(GTK_WINDOW(win), width, height);
  gtk_window_set_title(GTK_WINDOW(win), "YES/NO box");
  gtk_container_set_border_width(GTK_CONTAINER(win), 18);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(destroy), NULL);

  //Create BOX + Message label
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 18);
  GtkWidget *label = gtk_label_new(msg);

  //Create YES/NO Buttons
  GtkWidget *buttonbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  GtkWidget *button_yes = gtk_button_new_with_label("Yes");
  g_signal_connect(G_OBJECT(button_yes), "clicked", G_CALLBACK(set_yes), win);
  GtkWidget *button_no  = gtk_button_new_with_label("No");
  g_signal_connect(G_OBJECT(button_no) , "clicked", G_CALLBACK(set_no) , win);

  gtk_box_pack_end(GTK_BOX(buttonbox), button_no, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(buttonbox), button_yes , FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(box), label);
  gtk_box_pack_end(GTK_BOX(box), buttonbox, FALSE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(win), box);

  gtk_widget_show_all(win);

  gtk_main();

  return res;
}
