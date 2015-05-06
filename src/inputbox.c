/*
    Contains the YesNo dialogs
    Copyright (C) 2015 Marius Messerschmidt
*/
#include "inputbox.h"

GtkWidget *input;

void ok(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy)
{
  fprintf(stderr, "%s", gtk_entry_get_text(GTK_ENTRY(input)));
  gtk_widget_destroy(toDestroy);
}

void cancel(GtkWidget *w, GdkEvent *e, GtkWidget *toDestroy)
{
  gtk_widget_destroy(toDestroy);
}

short create_input_box_dialog(int argc, char **argv, int start)
{
  if(argc - (start+3) < 1)
    return -1;

  char *msg = argv[start+1];
  int width  = atoi(argv[start+2]);
  int height = atoi(argv[start+3]);

  char *init = NULL;

  if(argc - (start+4) >= 1)
    init = argv[start+4];

  //Create stuff
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(width > 0 && height > 0)
    gtk_window_resize(GTK_WINDOW(win), width, height);
  gtk_window_set_title(GTK_WINDOW(win), "INPUT box");
  gtk_container_set_border_width(GTK_CONTAINER(win), 18);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(destroy), NULL);

  //Create BOX + Message label
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 18);
  GtkWidget *label = gtk_label_new(msg);

  //Create Input Box
  input = gtk_entry_new();
  if(init != NULL)
      gtk_entry_set_text(GTK_ENTRY(input), init);


  //Create OK/CANCEL Buttons
  GtkWidget *buttonbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
  GtkWidget *button_ok = gtk_button_new_with_label("OK");
  g_signal_connect(G_OBJECT(button_ok), "clicked", G_CALLBACK(ok), win);
  GtkWidget *button_cancel  = gtk_button_new_with_label("Cancel");
  g_signal_connect(G_OBJECT(button_cancel) , "clicked", G_CALLBACK(cancel) , win);

  gtk_box_pack_end(GTK_BOX(buttonbox), button_cancel, FALSE, FALSE, 0);
  gtk_box_pack_end(GTK_BOX(buttonbox), button_ok , FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(box), label);
  gtk_box_pack_end(GTK_BOX(box), buttonbox, FALSE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), input, FALSE, TRUE, 0);
  gtk_container_add(GTK_CONTAINER(win), box);

  gtk_widget_show_all(win);

  gtk_main();

  return 0;
}
