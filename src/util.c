/*
  Contains some basic things
  Copyright (C) 2015 Marius Messerschmidt

*/
#define INCLUDE_VARS
#include "util.h"

void destroy(GtkWidget *w, GdkEvent *e, gpointer p)
{
  gtk_main_quit();
}

void reset_config(void)
{
  backtitle = NULL;
}

void set_backtitle(char *back)
{
  if(back != NULL)
    backtitle = back;
}

void apply_dialog_config(GtkWindow *w)
{
  if(backtitle != NULL)
  gtk_window_set_title(GTK_WINDOW(w), backtitle);
}
